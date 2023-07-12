/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mini_init.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum <kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/05 14:23:03 by kposthum      #+#    #+#                 */
/*   Updated: 2023/07/12 16:17:03 by kposthum      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include<minishell_parsing.h>

int	initialize(char *line, t_list **loc_var)
{
	t_input		*cmd;

	cmd = ft_calloc(sizeof(t_input), 1);
	if (!cmd)
		return (mem_err(), 1);
	cmd->loc_var = loc_var;
	cmd->comm_nr = ft_charcount(line, '|');
	cmd->commands = ft_calloc(sizeof(t_commands *), cmd->comm_nr);
	if (!cmd->commands)
		return (mem_err(), free(cmd), 1);
	return (0);
}

// void	free_struct2(t_commands *commands, char **temp)
// {
// 	size_t	i;

// 	i = 0;
// 	if (commands->infiles)
// 	{
// 		while (commands->infiles[i])
// 		{
// 			free(commands->infiles[i]->filename);
// 			free(commands->infiles[i]);
// 			i++;
// 		}
// 		free(commands->infiles);
// 	}
// 	i = 0;
// 	if (commands->outfiles)
// 	{
// 		while (commands->outfiles[i])
// 		{
// 			free(commands->outfiles[i]->filename);
// 			free(commands->outfiles[i]);
// 			i++;
// 		}
// 		free(commands->outfiles);
// 	}
// 	if (commands->args)
// 		ft_free(commands->args);
// 	free(commands);
// 	ft_free(temp);
// 	mem_err();
// }

// t_commands	*make_inout(char *input)
// {
// 	char		**temp;
// 	t_commands	*commands;

// 	temp = ft_split_whitespace(input);
// 	if (!temp)
// 		return (mem_err(), NULL);
// 	commands = ft_calloc(1, sizeof(t_commands));
// 	if (!commands)
// 		return (ft_free(temp), mem_err(), NULL);
// 	commands->infiles = check_infile(temp);
// 	commands->outfiles = check_outfile(temp);
// 	commands->args = trim_redir(temp);
// 	if (!commands->infiles | !commands->outfiles
// 		| !commands->args)
// 		return (free_struct2(commands, temp), NULL);
// 	commands->command = ft_strdup(commands->args[0]);
// 	if (!commands->command)
// 		return (free_struct2(commands, temp), NULL);
// 	ft_free(temp);
// 	return (commands);
// }

// void	free_struct1(t_input *cmd, size_t i, char **temp)
// {
// 	size_t	j;

// 	ft_free(temp);
// 	while (i > 0)
// 	{
// 		i--;
// 		j = 0;
// 		while (cmd->commands[i]->infiles[j] != NULL)
// 		{
// 			free(cmd->commands[i]->infiles[j]->filename);
// 			free(cmd->commands[i]->infiles[j]);
// 			j++;
// 		}
// 		free(cmd->commands[i]->infiles);
// 		j = 0;
// 		while (cmd->commands[i]->outfiles[j] != NULL)
// 		{
// 			free(cmd->commands[i]->outfiles[j]->filename);
// 			free(cmd->commands[i]->outfiles[j]);
// 			j++;
// 		}
// 		free(cmd->commands[i]->outfiles);
// 		free(cmd->commands[i]);
// 		i--;
// 	}
// 	free(cmd->commands);
// 	free(cmd);
// 	mem_err();
// }

// t_input	*make_struct(char *line)
// {
// 	t_input	*cmd;
// 	char	**temp;
// 	size_t	i;

// 	i = 0;
// 	cmd = ft_calloc(1, sizeof(t_input));
// 	if (!cmd)
// 		return (mem_err(), NULL);
// 	cmd->comm_nr = ft_charcount(line, '|') + 1;
// 	cmd->commands = ft_calloc(cmd->comm_nr + 1, sizeof(t_commands *));
// 	if (!cmd->commands)
// 		return (free(cmd), mem_err(), NULL);
// 	temp = ft_split_quotes(line, '|');
// 	if (!temp)
// 		return (free(cmd->commands), free(cmd), mem_err(), NULL);
// 	while (i < cmd->comm_nr)
// 	{
// 		cmd->commands[i] = make_inout(temp[i]);
// 		if (!cmd->commands[i])
// 			return (free_struct1(cmd, i, temp), NULL);
// 		i++;
// 	}
// 	ft_free(temp);
// 	return (cmd);
// }
