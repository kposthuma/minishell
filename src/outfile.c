/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   outfile.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum >kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/15 14:56:24 by kposthum      #+#    #+#                 */
/*   Updated: 2023/06/17 16:22:32 by kposthum      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include<minishell_parsing.h>

char	**trim_comm_out(char **comm)
{
	char	**comm_new;
	size_t	i;
	size_t	j;

	comm_new = ft_calloc(strofstrlen(comm) - 1, sizeof(char *));
	i = strofstrlen(comm) - 3;
	j = 0;
	while (j >= i)
	{
		comm_new[j] = ft_strdup(comm[j]);
		j++;
	}
	ft_free(comm);
	return (comm_new);
}

t_outf	*has_outfile(t_commands *commands)
{
	t_outf	*outfile;
	size_t	i;
	size_t	j;

	i = 0;
	j = UINT32_MAX;
	while (commands->command[i])
	{
		if (commands->command[i][0] == '>')
			j = i;
		i++;
	}
	if (j == UINT32_MAX)
		return (NULL);
	outfile = ft_calloc(1, sizeof(t_inf));
	if (ft_strncmp(commands->command[j], ">>", 3) == 0)
		outfile->append = true;
	else if (ft_strncmp(commands->command[j], ">", 2) == 0)
		outfile->append = false;
	outfile->filename = ft_strdup(commands->command[j + 1]);
	return (outfile);
}
