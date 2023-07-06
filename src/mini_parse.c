/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mini_parse.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum <kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/05 14:23:03 by kposthum      #+#    #+#                 */
/*   Updated: 2023/07/06 12:59:00 by kposthum      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include<minishell_parsing.h>

t_commands	*parse_input(char *input, t_input *cmd, size_t i)
{
	char		**temp;
	t_commands	*commands;

	temp = ft_split_whitespace(input);
	if (!temp)
		return (mem_err(), NULL);
	commands = ft_calloc(1, sizeof(t_commands));
	if (!commands)
		return (ft_free(temp), mem_err(), NULL);
	commands->infiles = check_infile(temp);
	commands->outfiles = check_outfile(temp);
	commands->args = trim_redir(temp);
	commands->command = ft_strdup(commands->args[0]);
	if (!commands->infiles | !commands->outfiles
		| !commands->args | !commands->command)
		return (NULL); //proper alloc handling
	ft_free(temp);
	return (commands);
}

void	free_struct(t_input *cmd, size_t i, char **temp)
{
	size_t	j;

	ft_free(temp);
	while (i > 0)
	{
		i--;
		j = 0;
		while (cmd->commands[i]->infiles[j] != NULL)
		{
			free(cmd->commands[i]->infiles[j]->filename);
			free(cmd->commands[i]->infiles[j]);
			j++;
		}
		j = 0;
		while (cmd->commands[i]->outfiles[j] != NULL)
		{
			free(cmd->commands[i]->outfiles[j]->filename);
			free(cmd->commands[i]->outfiles[j]);
			j++;
		}
		free(cmd->commands[i]);
	}
	free(cmd);
}

t_input	*parse_line(char *line)
{
	t_input	*cmd;
	char	**temp;
	size_t	i;

	i = 0;
	cmd = ft_calloc(1, sizeof(t_input));
	if (!cmd)
		return (mem_err(), NULL);
	cmd->comm_nr = ft_charcount(line, '|') + 1;
	cmd->commands = ft_calloc(cmd->comm_nr + 1, sizeof(t_commands *));
	if (!cmd->commands)
		return (free(cmd), mem_err(), NULL);
	temp = ft_split_quotes(line, '|');
	if (!temp)
		return (free(cmd->commands), free(cmd), mem_err(), NULL);
	while (i < cmd->comm_nr)
	{
		cmd->commands[i] = parse_input(temp[i], cmd, i);
		if (!cmd->commands[i])
			return (free_struct(cmd, i, temp), mem_err(), NULL);
		i++;
	}
	ft_free(temp);
	return (cmd);
}
