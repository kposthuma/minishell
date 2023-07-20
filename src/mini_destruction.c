/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mini_destruction.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum <kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/20 12:28:08 by kposthum      #+#    #+#                 */
/*   Updated: 2023/07/20 12:37:32 by kposthum      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include<minishell_parsing.h>

static void	free_infile(t_list **inf)
{
	t_list	*head;
	t_inf	*infile;

	head = *inf;
	while (head != NULL)
	{
		infile = (t_inf *)head->cnt;
		free(infile->filename);
		head = head->nxt;
	}
	ft_lstclear(inf);
}

static void	free_outfile(t_list **outf)
{
	t_list	*head;
	t_outf	*outfile;

	head = *outf;
	while (head != NULL)
	{
		outfile = (t_outf *)head->cnt;
		free(outfile->filename);
		head = head->nxt;
	}
	ft_lstclear(outf);
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
