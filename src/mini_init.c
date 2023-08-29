/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mini_init.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum <kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/05 14:23:03 by kposthum      #+#    #+#                 */
/*   Updated: 2023/08/29 13:49:26 by kposthum      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell_parsing.h>

static char	**ft_trim_quotes_double(char **src)
{
	size_t	i;

	i = 0;
	if (!src)
		return (NULL);
	while (src && src[i])
	{
		src[i] = ft_trim_quotes(src[i]);
		i++;
	}
	return (src);
}

static	void	construct_command(t_commands *command)
{
	if (!command->args[0])
		command->command = NULL;
	else
		command->command = ft_strdup(command->args[0]);
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
	line[i] = check_infile(command, line[i]);
	if (!line[i])
		return (free_command_struct(command), NULL);
	line[i] = check_outfile(command, line[i]);
	if (!line[i])
		return (free_command_struct(command), NULL);
	command->args = ft_trim_quotes_double(ft_split_whitespace(line[i]));
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
	// int			stat;
	t_input		*cmd;
	char		*str;
	char		**temp;

	if (parse_line(line) == false)
		return (258);
	str = mini_expansion(line, loc_var);
	if (!str)
		return (mem_err(), 1);
	if (ft_strlen(str) == 0)
		return (0);
	temp = ft_split_quotes(str, '|');
	if (!temp)
		return (mem_err(), free(str), 1);
	cmd = build_cmd(str, temp, loc_var);
	free(str);
	ft_free(temp);
	if (!cmd)
		return (mem_err(), 1);
	print_all_the_shit(cmd);
	// stat = executor(cmd);
	destroy_cmd(cmd);
	return (ft_strlen(line));
	// return (stat);
}
