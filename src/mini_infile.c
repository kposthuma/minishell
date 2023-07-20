/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mini_infile.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum <kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/13 14:06:30 by kposthum      #+#    #+#                 */
/*   Updated: 2023/07/20 14:36:04 by kposthum      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include<minishell_parsing.h>

// creates a string for the infile struct 
static char	*make_filename(char *temp)
{
	while (*temp == '<' || ft_isspace(*temp) == 0)
		temp++;
	return (ft_strdup(temp));
}

// are we heredoc, or are we infile?
static bool	check_heredoc(char *temp)
{
	if (ft_charcount(temp, '<') == 2)
		return (true);
	else
		return (false);
}

// check if there are any infile redirects
char	*check_infile(t_commands *command, char *line)
{
	char	*temp;
	t_inf	*inf;
	t_list	*new;

	while (ft_strchr_quotes(line, '<') != NULL)
	{
		temp = ft_substr(ft_strchr_quotes(line, '<'), 0, redir_len(line, '<'));
		inf = ft_calloc(sizeof(t_inf), 1);
		if (!temp || !inf)
			return (NULL); //proper free everything plox
		inf->heredoc = check_heredoc(temp);
		inf->filename = make_filename(temp);
		line = ft_string_snip(line, temp);
		if (!inf->filename || !line)
			return (mem_err(), free(line), NULL); //proper free everything plox
		new = ft_lstnew((void *)inf);
		ft_lstadd_back(command->infiles, new);
		free(temp);
	}
	return (line);
}
