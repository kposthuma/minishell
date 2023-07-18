/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mini_outfile.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum <kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/13 14:06:30 by kposthum      #+#    #+#                 */
/*   Updated: 2023/07/13 15:13:19 by kposthum      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include<minishell_parsing.h>

static char	*make_filename(char *temp)
{
	char	*name;

	while (*temp == '>' || ft_isspace(*temp) == 1)
		temp++;
	return (ft_strdup(temp));
}

static bool	check_append(char *temp)
{
	if (ft_charcount(temp, '>') == 2)
		return (true);
	else
		retrun (false);
}

char	*check_outfile(t_commands *command, char *line)
{
	char	*temp;
	t_outf	*outf;
	t_list	*new;

	while (ft_strchr(line, '>') != NULL)
	{
		temp = ft_substr(ft_strchr(line, '>'), 0, redir_len(line, '>'));
		outf = ft_calloc(sizeof(t_outf), 1);
		if (!temp || !outf)
			return (mem_err(), free(line), NULL); //proper free everything plox
		outf->append = check_heredoc(temp);
		outf->filename = make_filname(temp);
		line = ft_string_snip(line, temp);
		if (!outf->filename || !line)
			return (mem_err(), free(line), NULL); //proper free everything plox
		new = ft_lstnew((void *)outf);
		ft_lstadd_back(command->outfiles, new);
		free(temp);
	}
	return (line);
}
// static size_t	redir_count(char **input, char c)
// {
// 	size_t	i;
// 	size_t	j;

// 	i = 0;
// 	j = 0;
// 	while (input[i])
// 	{
// 		if (input[i][0] == c)
// 			j++;
// 		i++;
// 	}
// 	return (j);
// }

// static t_outf	*make_outf_struct(char **input, size_t i)
// {
// 	t_outf	*outfile;
// 	size_t	j;

// 	j = 0;
// 	while (input[i][j] == '>')
// 		j++;
// 	if (j > 2)
// 		return (NULL); //syntax error message?
// 	outfile = ft_calloc(1, sizeof(t_outf));
// 	if (!outfile)
// 		return (NULL); //proper alloc handling
// 	if (input[i][j] != '\0')
// 		outfile->filename = ft_substr(input[i], j, ft_strlen(input[i]) - j);
// 	else if (input[i + 1] && input[i + 1][0] != '>')
// 		outfile->filename = ft_strdup(input[i + 1]);
// 	else
// 		return (free(outfile), NULL); //syntax error message?
// 	if (!outfile->filename)
// 		return (NULL); //proper alloc handling
// 	outfile->append = j - 1;
// 	return (outfile);
// }

// t_outf	**check_outfile(char **input)
// {
// 	size_t	i;
// 	size_t	j;
// 	t_outf	**outfiles;

// 	i = 0;
// 	j = redir_count(input, '>');
// 	outfiles = ft_calloc(j + 1, sizeof(t_outf *));
// 	if (!outfiles)
// 		return (mem_err(), NULL);
// 	if (j == 0)
// 		return (outfiles);
// 	while (input[i])
// 	{
// 		if (input[i][0] == '>')
// 		{
// 			outfiles[j] = make_outf_struct(input, i);
// 			if (!outfiles[j])
// 				return (NULL); //proper alloc handling
// 			j++;
// 		}
// 		i++;
// 	}
// 	return (outfiles);
// }
