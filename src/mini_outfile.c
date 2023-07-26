/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mini_outfile.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum <kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/13 14:06:30 by kposthum      #+#    #+#                 */
/*   Updated: 2023/07/26 17:04:04 by kposthum      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include<minishell_parsing.h>

// makes filename for the outfile struct
static char	*make_filename(char *temp)
{
	char	*trim;

	while (*temp && (*temp == '>' || ft_isspace(*temp) == 0))
		temp++;
	trim = ft_strdup(temp);
	return (ft_trim_quotes(trim));
}

// are we append, or are we truncate 
static bool	check_append(char *temp)
{
	if (ft_charcount(temp, '>') == 2)
		return (true);
	else
		return (false);
}

static void	mem_fail_dest(char *temp, t_outf *outf, char *line)
{
	free(temp);
	free(outf->filename);
	free(outf);
	free(line);
}

// checks if there are any outfile redirects
char	*check_outfile(t_commands *command, char *line)
{
	char	*temp;
	t_outf	*outf;
	t_list	*new;

	while (ft_strchr_quotes(line, '>') != NULL)
	{
		temp = ft_substr(ft_strchr_quotes(line, '>'), 0, redir_len(line, '>'));
		outf = ft_calloc(sizeof(t_outf), 1);
		if (!temp || !outf)
			return (free(temp), free(outf), NULL);
		outf->append = check_append(temp);
		outf->filename = make_filename(temp);
		line = ft_string_snip(line, temp);
		if (!outf->filename || !line)
			return (mem_fail_dest(temp, outf, line), NULL);
		new = ft_lstnew((void *)outf);
		if (!new)
			return (mem_fail_dest(temp, outf, line), NULL);
		ft_lstadd_back(command->outfiles, new);
		free(temp);
	}
	return (line);
}
