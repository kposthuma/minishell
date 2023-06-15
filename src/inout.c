/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   inout.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum <kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/13 14:06:30 by kposthum      #+#    #+#                 */
/*   Updated: 2023/06/15 11:12:57 by kposthum      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include<minishell_parsing.h>

char	**trim_comm_out(char **comm)
{
	char	**comm_new;
	size_t	i;

	comm_new = ft_calloc(strofstrlen(comm) - 1, sizeof(char *));
	i = strofstrlen(comm) - 3;
	while (i >= 0)
	{
		comm_new[i] = ft_strdup(comm[i]);
		i--;
	}
	ft_free(comm);
	return (comm_new);
}

t_outf	*has_outfile(t_commands *cmd)
{
	t_outf	*outfile;
	size_t	i;

	i = strofstrlen(cmd->commands[cmd->comm_nr - 1]);
	if (i < 3)
		return (NULL);
	i -= 2;
	if (cmd->commands[cmd->comm_nr - 1][i][0] != '>')
		return (NULL);
	outfile = ft_calloc(1, sizeof(t_inf));
	if (ft_strncmp(cmd->commands[cmd->comm_nr - 1][i], ">>", 3) == 0)
		outfile->append = true;
	else if (ft_strncmp(cmd->commands[cmd->comm_nr - 1][i], ">", 2) == 0)
		outfile->append = false;
	outfile->filename = ft_strdup(cmd->commands[cmd->comm_nr - 1][i + 1]);
	return (outfile);
}

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

t_inf	*has_infile(t_commands *cmd)
{
	t_inf	*infile;

	if (cmd->commands[0][0][0] != '<')
		return (NULL);
	infile = ft_calloc(1, sizeof(t_inf));
	if (ft_strncmp(cmd->commands[0][0], "<<<", 4) == 0)
		infile->in_type = 2;
	else if (ft_strncmp(cmd->commands[0][0], "<<", 3) == 0)
		infile->in_type = 1;
	else if (ft_strncmp(cmd->commands[0][0], "<", 2) == 0)
		infile->in_type = 0;
	infile->filename = ft_strdup(cmd->commands[0][1]);
	return (infile);
}
