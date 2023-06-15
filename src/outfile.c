/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   outfile.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum <kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/15 14:56:24 by kposthum      #+#    #+#                 */
/*   Updated: 2023/06/15 14:56:33 by kposthum      ########   odam.nl         */
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
	while (j <= i)
	{
		comm_new[j] = ft_strdup(comm[j]);
		j++;
	}
	ft_free(comm);
	return (comm_new);
}

t_outf	*has_outfile(t_commands *cmd)
{
	t_outf	*outfile;
	size_t	i;

	if (strofstrlen(cmd->commands[cmd->comm_nr - 1]) < 2)
		return (NULL);
	i = strofstrlen(cmd->commands[cmd->comm_nr - 1]) - 2;
	if (cmd->commands[cmd->comm_nr - 1][i][0] != '>')
		return (NULL);
	outfile = ft_calloc(1, sizeof(t_outf));
	if (ft_strncmp(cmd->commands[cmd->comm_nr - 1][i], ">", 2) == 0)
		outfile->append = false;
	else if (ft_strncmp(cmd->commands[cmd->comm_nr - 1][i], ">>", 3) == 0)
		outfile->append = true;
	outfile->filename = ft_strdup(cmd->commands[cmd->comm_nr - 1][i + 1]);
	return (outfile);
}
