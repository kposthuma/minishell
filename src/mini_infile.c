/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mini_infile.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum <kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/13 14:06:30 by kposthum      #+#    #+#                 */
/*   Updated: 2023/07/06 12:58:01 by kposthum      ########   odam.nl         */
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

static t_inf	*make_inf_struct(char **input, size_t i)
{
	t_inf	*infile;
	size_t	j;

	j = 0;
	while (input[i][j] == '<')
		j++;
	if (j > 2)
		return (NULL); //sntax error message?
	infile = ft_calloc(1, sizeof(t_inf));
	if (!infile)
		return (mem_err(), NULL);
	if (input[i][j] != '\0')
		infile->filename = ft_substr(input[i], j, ft_strlen(input[i]) - j);
	else if (input[i + 1] && input[i + 1][0] != '<')
		infile->filename = ft_strdup(input[i + 1]);
	else
		return (free(infile), NULL); //syntax error message?
	if (!infile->filename)
		return (free(infile), NULL); //proper alloc handling
	infile->heredoc = j - 1;
	return (infile);
}

t_inf	**check_infile(char **input)
{
	size_t	i;
	size_t	j;
	t_inf	**infiles;

	i = 0;
	j = redir_count(input, '<');
	infiles = ft_calloc(j + 1, sizeof(t_inf *));
	if (!infiles)
		return (mem_err(), NULL);
	if (j == 0)
		return (infiles);
	j = 0;
	while (input[i])
	{
		if (input[i][0] == '<')
		{
			infiles[j] = make_inf_struct(input, i);
			if (!infiles[j])
				return (NULL); //proper alloc handling
			j++;
		}
		i++;
	}
	return (infiles);
}
