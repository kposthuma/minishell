/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mini_destruction.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum <kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/20 12:28:08 by kposthum      #+#    #+#                 */
/*   Updated: 2023/09/10 14:08:39 by kposthum      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell_parsing.h>

static void	free_infile(t_list **inf)
{
	t_list	*head;
	t_inf	*infile;

	head = *inf;
	while (head != NULL)
	{
		infile = (t_inf *)head->cnt;
		head = head->nxt;
		free(infile->filename);
		free(infile);
	}
	ft_lstclear(inf);
	free(inf);
}

static void	free_outfile(t_list **outf)
{
	t_list	*head;
	t_outf	*outfile;

	head = *outf;
	while (head != NULL)
	{
		outfile = (t_outf *)head->cnt;
		head = head->nxt;
		free(outfile->filename);
		free(outfile);
	}
	ft_lstclear(outf);
	free(outf);
}

void	free_command_struct(t_commands *command)
{
	free(command->infiles);
	free(command->outfiles);
	free(command);
}

void	free_cmd(t_input *cmd, size_t i)
{
	if (i != 0)
	{
		while (i > 0)
		{
			i--;
			free_infile(cmd->commands[i]->infiles);
			free_outfile(cmd->commands[i]->outfiles);
			free(cmd->commands[i]->command);
			ft_free(cmd->commands[i]->args);
			free(cmd->commands[i]);
		}
		free(cmd->commands);
		free(cmd);
	}
}

void	destroy_cmd(t_input *cmd)
{
	size_t	i;

	i = 0;
	while (i < cmd->comm_nr)
	{
		free(cmd->commands[i]->command);
		ft_free(cmd->commands[i]->args);
		free_infile(cmd->commands[i]->infiles);
		free_outfile(cmd->commands[i]->outfiles);
		free(cmd->commands[i]);
		i++;
	}
	free(cmd->commands);
	free(cmd);
}
