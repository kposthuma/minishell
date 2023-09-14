/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mini_infile.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum <kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/13 14:06:30 by kposthum      #+#    #+#                 */
/*   Updated: 2023/09/14 17:20:47 by kposthum      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell_parsing.h>

// creates a string for the infile struct 
static char	*make_filename(char *temp, t_list **loc_var)
{
	char	*trim;

	while (*temp && (*temp == '<' || ft_isspace(*temp) == 1))
		temp++;
	trim = mini_expansion(temp, loc_var);
	return (ft_trim_quotes(trim));
}

// are we heredoc, or are we infile?
static bool	check_heredoc(char *temp)
{
	if (ft_charcount(temp, '<') == 2)
		return (true);
	else
		return (false);
}

static void	mem_fail_dest(char *temp, t_inf *inf, char *line)
{
	free(temp);
	free(inf->filename);
	free(inf);
	free(line);
}

// check if there are any infile redirects
char	*check_infile(t_commands *command, char *line, t_list **loc_var)
{
	char	*temp;
	t_inf	*inf;
	t_list	*new;

	while (ft_strchr_quotes(line, '<') != NULL)
	{
		temp = ft_substr(ft_strchr_quotes(line, '<'), 0, redir_len(line, '<'));
		inf = ft_calloc(sizeof(t_inf), 1);
		if (!temp || !inf)
			return (free(temp), free(inf), NULL);
		inf->heredoc = check_heredoc(temp);
		inf->filename = make_filename(temp, loc_var);
		line = ft_string_snip(line, temp);
		if (!inf->filename || !line)
			return (mem_fail_dest(temp, inf, line), NULL);
		new = ft_lstnew((void *)inf);
		if (!new)
			return (mem_fail_dest(temp, inf, line), NULL);
		ft_lstadd_back(command->infiles, new);
		free(temp);
	}
	return (line);
}
