/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mini_init.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum <kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/05 14:23:03 by kposthum      #+#    #+#                 */
/*   Updated: 2023/07/25 17:04:20 by kposthum      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include<minishell_parsing.h>

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

static void	print_all_the_shit(t_input *cmd)
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

static char	**ft_trim_quotes_double(char **src)
{
	size_t	i;

	i = 0;
	while (src && src[i])
	{
		src[i] = ft_trim_quotes(src[i]);
		i++;
	}
	return (src);
}

// makes the individual commands
t_commands	*construct(char	*line)
{
	t_commands	*command;

	command = ft_calloc(sizeof(t_commands), 1);
	if (!command)
		return (mem_err(), NULL);
	command->infiles = ft_calloc(sizeof(t_list *), 1);
	command->outfiles = ft_calloc(sizeof(t_list *), 1);
	if (!command->infiles || !command->outfiles)
		return (free(command->infiles), free(command->outfiles),
			free(command), NULL);
	line = check_infile(command, line);
	line = check_outfile(command, line);
	command->args = ft_trim_quotes_double(ft_split_whitespace(line));
	if (command->args[0] != NULL)
		command->command = ft_strdup(command->args[0]);
	else
		command->command = NULL;
	return (command);
}

// makes the main struct to be passed to the executor
int	initialize(char *line, t_list **loc_var)
{
	t_input		*cmd;
	char		**temp;
	size_t		i;

	line = mini_expansion(line, loc_var);
	cmd = ft_calloc(sizeof(t_input), 1);
	if (!cmd)
		return (mem_err(), 1);
	cmd->loc_var = loc_var;
	cmd->comm_nr = ft_charcount(line, '|') + 1;
	cmd->commands = ft_calloc(sizeof(t_commands *), cmd->comm_nr);
	if (!cmd->commands)
		return (mem_err(), free(cmd), 1);
	temp = ft_split(line, '|');
	i = 0;
	while (i < cmd->comm_nr)
	{
		cmd->commands[i] = construct(temp[i]);
		i++;
	}
	print_all_the_shit(cmd);
	destroy_cmd(cmd);
	return (ft_strlen(line));
}
