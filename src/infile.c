/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   infile.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum <kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/13 14:06:30 by kposthum      #+#    #+#                 */
/*   Updated: 2023/06/17 16:09:56 by kposthum      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include<minishell_parsing.h>

char	**trim_comm_in(char **comm)
{
	char	**comm_new;
	size_t	i;

	comm_new = ft_calloc(strofstrlen(comm) - 1, sizeof(char *));
	i = 2;
	while (comm[i])
	{
		comm_new[i - 2] = ft_strdup(comm[i]);
		i++;
	}
	ft_free(comm);
	return (comm_new);
}

t_inf	*has_infile(t_commands *commands)
{
	t_inf	*infile;
	size_t	i;
	size_t	j;

	i = 0;
	j = UINT32_MAX;
	while (commands->command[i])
	{
		if (commands->command[i][0] == '<')
			j = i;
		i++;
	}
	if (j == UINT32_MAX)
		return (NULL);
	infile = ft_calloc(1, sizeof(t_inf));
	if (ft_strncmp(commands->command[j], "<<<", 4) == 0)
		infile->in_type = 2;
	else if (ft_strncmp(commands->command[j], "<<", 3) == 0)
		infile->in_type = 1;
	else if (ft_strncmp(commands->command[j], "<", 2) == 0)
		infile->in_type = 0;
	infile->filename = ft_strdup(commands->command[j + 1]);
	return (infile);
}
