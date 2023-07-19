/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mini_infile.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum <kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/13 14:06:30 by kposthum      #+#    #+#                 */
/*   Updated: 2023/07/19 11:23:57 by kposthum      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include<minishell_parsing.h>

static char	*make_filename(char *temp)
{
	while (*temp == '<' || ft_isspace(*temp) == 1)
		temp++;
	return (ft_strdup(temp));
}

static bool	check_heredoc(char *temp)
{
	if (ft_charcount(temp, '<') == 2)
		return (true);
	else
		return (false);
}

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

// static t_inf	*make_inf_struct(char **input, size_t i)
// {
// 	t_inf	*infile;
// 	size_t	j;

// 	j = 0;
// 	while (input[i][j] == '<')
// 		j++;
// 	if (j > 2)
// 		return (NULL); //sntax error message?
// 	infile = ft_calloc(1, sizeof(t_inf));
// 	if (!infile)
// 		return (mem_err(), NULL);
// 	if (input[i][j] != '\0')
// 		infile->filename = ft_substr(input[i], j, ft_strlen(input[i]) - j);
// 	else if (input[i + 1] && input[i + 1][0] != '<')
// 		infile->filename = ft_strdup(input[i + 1]);
// 	else
// 		return (free(infile), NULL); //syntax error message?
// 	if (!infile->filename)
// 		return (free(infile), NULL); //proper alloc handling
// 	infile->heredoc = j - 1;
// 	return (infile);
// }

// t_inf	**check_infile(char **input)
// {
// 	size_t	i;
// 	size_t	j;
// 	t_inf	**infiles;

// 	i = 0;
// 	j = redir_count(input, '<');
// 	infiles = ft_calloc(j + 1, sizeof(t_inf *));
// 	if (!infiles)
// 		return (mem_err(), NULL);
// 	if (j == 0)
// 		return (infiles);
// 	j = 0;
// 	while (input[i])
// 	{
// 		if (input[i][0] == '<')
// 		{
// 			infiles[j] = make_inf_struct(input, i);
// 			if (!infiles[j])
// 				return (NULL); //proper alloc handling
// 			j++;
// 		}
// 		i++;
// 	}
// 	return (infiles);
// }
