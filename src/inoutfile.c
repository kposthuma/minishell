/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   inoutfile.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum <kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/13 14:06:30 by kposthum      #+#    #+#                 */
/*   Updated: 2023/06/21 14:46:13 by kposthum      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include<minishell_parsing.h>

// char	**trim_comm_in(char **comm)
// {
// 	char	**comm_new;
// 	size_t	i;

// 	comm_new = ft_calloc(strofstrlen(comm) - 1, sizeof(char *));
// 	i = 2;
// 	while (comm[i])
// 	{
// 		comm_new[i - 2] = ft_strdup(comm[i]);
// 		i++;
// 	}
// 	ft_free(comm);
// 	return (comm_new);
// }

char	*trim_in_out(char *string)
{
	char	**temp;
	char	*trimmed;
	size_t	i;

	temp = ft_split_quotes(string, ' ');
	i = 0;
	while (temp[i])
	{
		if (temp[i][0] == '<' || temp[i][0] == '>')
			i++;
		else
			trimmed = ft_strjoingnl(trimmed, temp[i]);
		i++;
	}
	ft_free(temp);
	return (trimmed);
}

size_t	file_len(char *temp)
{
	size_t	i;

	i = 0;
	while (temp[i + 2])
	{
		if (temp[i + 2] == ' ')
			break ;
		i++;
	}
	return (i);
}

t_inf	*has_infile(char *command)
{
	t_inf	*infile;
	char	*temp;
	size_t	i;

	temp = ft_strrchr(command, '<');
	if (!temp)
		return (NULL);
	infile = ft_calloc(1, sizeof(t_inf));
	if (ft_strnstr(temp - 2, "<<< ", 4) == 0)
		infile->in_type = 2;
	else if (ft_strnstr(temp - 1, "<< ", 3) == 0)
		infile->in_type = 1;
	else if (ft_strnstr(temp, "< ", 2) == 0)
		infile->in_type = 0;
	else
		return (syntax_error_files(temp), free(infile), NULL);
	i = file_len(temp);
	if (i == 0)
		return (syntax_error_files(temp), free(infile), NULL);
	infile->filename = ft_substr(temp, 0, i);
	return (infile);
}

t_outf	*has_outfile(char *command)
{
	t_outf	*outfile;
	char	*temp;
	size_t	i;

	temp = ft_strrchr(command, '>');
	if (!temp)
		return (NULL);
	outfile = ft_calloc(1, sizeof(t_outf));
	if (ft_strnstr(temp - 1, ">> ", 3) == 0)
		outfile->append = true;
	else if (ft_strnstr(temp, "> ", 2) == 0)
		outfile->append = false;
	else
		return (syntax_error_files(temp), free(outfile), NULL);
	i = file_len(temp);
	if (i == 0)
		return (syntax_error_files(temp), free(outfile), NULL);
	outfile->filename = ft_substr(temp, 0, i);
	return (outfile);
}
