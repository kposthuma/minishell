/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mini_init.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum <kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/05 14:23:03 by kposthum      #+#    #+#                 */
/*   Updated: 2023/09/20 14:33:45 by kposthum      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell_parsing.h>

static	void	construct_command(t_commands *command)
{
	if (!command->args[0])
		command->command = NULL;
	else
		command->command = ft_strdup(command->args[0]);
}

static	char	**make_arg(char *line, t_input *cmd)
{
	char	**arg;
	char	*temp;
	size_t	i;

	arg = ft_split_whitespace(line);
	if (!arg)
		return (mem_err(), NULL);
	i = 0;
	while (arg[i])
	{
		temp = arg[i];
		arg[i] = ft_trim_quotes(mini_expansion(arg[i], cmd->loc_var));
		printf("%s\n", arg[i]);
		free(temp);
		if (!arg[i])
			return (ft_free(arg), mem_err(), NULL);
		i++;
	}
	return (arg);
}

// makes the individual command structs
static t_commands	*construct_argument(char **line, size_t i, t_input *cmd)
{
	t_commands	*command;

	command = ft_calloc(sizeof(t_commands), 1);
	if (!command)
		return (NULL);
	command->infiles = ft_calloc(sizeof(t_list *), 1);
	command->outfiles = ft_calloc(sizeof(t_list *), 1);
	if (!command->infiles || !command->outfiles)
		return (free(command->infiles), free(command->outfiles),
			free(command), NULL);
	line[i] = check_infile(command, line[i], cmd->loc_var);
	if (!line[i])
		return (free_command_struct(command), NULL);
	line[i] = check_outfile(command, line[i], cmd->loc_var);
	if (!line[i])
		return (free_command_struct(command), NULL);
	command->args = make_arg(line[i], cmd);
	if (!command->args)
		return (free_command_struct(command), free(line[i]), NULL);
	command->args = check_vars(command->args, cmd);
	construct_command(command);
	return (command);
}

// split up for fewer lines per function
static t_input	*build_cmd(char *line, char **temp, t_list **loc_var)
{
	t_input		*cmd;
	size_t		i;

	cmd = ft_calloc(sizeof(t_input), 1);
	if (!cmd)
		return (NULL);
	cmd->loc_var = loc_var;
	cmd->comm_nr = ft_charcount(line, '|') + 1;
	cmd->commands = ft_calloc(sizeof(t_commands *), cmd->comm_nr);
	if (!cmd->commands)
		return (free(cmd), NULL);
	i = 0;
	while (cmd != NULL && i < cmd->comm_nr)
	{
		cmd->commands[i] = construct_argument(temp, i, cmd);
		if (!cmd->commands[i])
			return (free_cmd(cmd, i), NULL);
		i++;
	}
	return (cmd);
}

// makes the main struct to be passed to the executor
int	initialize(char *line, t_list **loc_var)
{
	t_input		*cmd;
	char		**temp;
	int			stat;

	if (parse_line(line) == false)
		return (258);
	temp = ft_split_quotes(line, '|');
	if (!temp)
		return (mem_err(), 1);
	cmd = build_cmd(line, temp, loc_var);
	ft_free(temp);
	if (!cmd)
		return (mem_err(), 1);
	stat = ft_strlen(line);
	// stat = executor(cmd);
	print_all_the_shit(cmd);
	destroy_cmd(cmd);
	return (stat);
}
