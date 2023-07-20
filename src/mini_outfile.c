/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mini_outfile.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum <kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/13 14:06:30 by kposthum      #+#    #+#                 */
/*   Updated: 2023/07/20 14:36:14 by kposthum      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include<minishell_parsing.h>

// makes filename for the outfile struct
static char	*make_filename(char *temp)
{
	while (*temp == '>' || ft_isspace(*temp) == 0)
		temp++;
	return (ft_strdup(temp));
}

// are we append, or are we truncate 
static bool	check_append(char *temp)
{
	if (ft_charcount(temp, '>') == 2)
		return (true);
	else
		return (false);
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
			return (mem_err(), free(line), NULL); //proper free everything plox
		outf->append = check_append(temp);
		outf->filename = make_filename(temp);
		line = ft_string_snip(line, temp);
		if (!outf->filename || !line)
			return (mem_err(), free(line), NULL); //proper free everything plox
		new = ft_lstnew((void *)outf);
		ft_lstadd_back(command->outfiles, new);
		free(temp);
	}
	return (line);
}
