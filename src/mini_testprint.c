/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mini_testprint.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum <kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/26 14:27:47 by kposthum      #+#    #+#                 */
/*   Updated: 2023/08/29 13:54:49 by kposthum      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell_parsing.h>

static void	prinf(t_list **inf)
{
	t_inf	*yes;

	for (t_list	*head = *inf; head != NULL; head = head->nxt)
	{
		yes = (t_inf *)head->cnt;
		if (yes->heredoc == true)
			ft_printf("heredoc delimiter: %s\n", yes->filename);
		else
			ft_printf("infile name: %s\n", yes->filename);
	}
}

static void	proutf(t_list **outf)
{
	t_outf	*yes;

	for (t_list	*head = *outf; head != NULL; head = head->nxt)
	{
		yes = (t_outf *)head->cnt;
		if (yes->append == true)
			ft_printf("append, outfile name: %s\n", yes->filename);
		else
			ft_printf("truncate, outfile name: %s\n", yes->filename);
	}
}

void	print_all_the_shit(t_input *cmd)
{
	ft_printf("comm_nr: %d\n", cmd->comm_nr);
	for (size_t i = 0; i < cmd->comm_nr; i++)
	{
		ft_printf("command: %s\nargs: ", cmd->commands[i]->command);
		print_charpp(cmd->commands[i]->args);
		ft_printf("\n");
		prinf(cmd->commands[i]->infiles);
		proutf(cmd->commands[i]->outfiles);
	}
}
