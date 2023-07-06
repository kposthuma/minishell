/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mini_outfile.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum <kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/13 14:06:30 by kposthum      #+#    #+#                 */
/*   Updated: 2023/07/06 12:57:56 by kposthum      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include<minishell_parsing.h>

static size_t	redir_count(char **input, char c)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (input[i])
	{
		if (input[i][0] == c)
			j++;
		i++;
	}
	return (j);
}

static t_outf	*make_outf_struct(char **input, size_t i)
{
	t_outf	*outfile;
	size_t	j;

	j = 0;
	while (input[i][j] == '>')
		j++;
	if (j > 2)
		return (NULL); //syntax error message?
	outfile = ft_calloc(1, sizeof(t_outf));
	if (!outfile)
		return (NULL); //proper alloc handling
	if (input[i][j] != '\0')
		outfile->filename = ft_substr(input[i], j, ft_strlen(input[i]) - j);
	else if (input[i + 1] && input[i + 1][0] != '>')
		outfile->filename = ft_strdup(input[i + 1]);
	else
		return (free(outfile), NULL); //syntax error message?
	if (!outfile->filename)
		return (NULL); //proper alloc handling
	outfile->append = j - 1;
	return (outfile);
}

t_outf	**check_outfile(char **input)
{
	size_t	i;
	size_t	j;
	t_outf	**outfiles;

	i = 0;
	j = redir_count(input, '>');
	outfiles = ft_calloc(j + 1, sizeof(t_outf *));
	if (!outfiles)
		return (mem_err(), NULL);
	if (j == 0)
		return (outfiles);
	while (input[i])
	{
		if (input[i][0] == '>')
		{
			outfiles[j] = make_outf_struct(input, i);
			if (!outfiles[j])
				return (NULL); //proper alloc handling
			j++;
		}
		i++;
	}
	return (outfiles);
}
