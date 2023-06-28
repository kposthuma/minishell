/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum <kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/29 09:22:23 by kposthum      #+#    #+#                 */
/*   Updated: 2023/06/28 10:59:05 by kposthum      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include<minishell_parsing.h>

void	sigfunc(int signum)
{
	printf("aapjes, %i", signum);
	exit(signum);
}

t_commands	*parse_input(char *input)
{
	char		**temp;
	t_commands	*commands;

	temp = ft_split_whitespace(input);
	commands = ft_calloc(1, sizeof(t_commands));
	commands->infile = check_infile(temp);
	commands->outfile = check_outfile(temp);
	commands->args = trim_redir(temp);
	commands->command = ft_strdup(commands->args[0]);
	ft_free(temp);
	return (commands);
}

t_input	*parse_line(char *line)
{
	t_input	*cmd;
	char	**temp;
	size_t	i;

	i = 0;
	cmd = ft_calloc(1, sizeof(t_input));
	cmd->comm_nr = ft_charcount(line, '|') + 1;
	cmd->commands = ft_calloc(cmd->comm_nr + 1, sizeof(t_commands *));
	temp = ft_split_quotes(line, '|');
	while (i < cmd->comm_nr)
	{
		cmd->commands[i] = parse_input(temp[i]);
		i++;
	}
	ft_free(temp);
	return (cmd);
}

int	main(void)
{
	static char	*line;
	t_input		*cmd;

	signal(SIGINT, sigfunc);
	while (true)
	{
		line = readline("KAAS% ");
		if (!line)
			return (printf("exit\n"), 0);
		if (line && *line)
			add_history(line);
		cmd = parse_line(line);
		if (ft_strncmp(line, "exit", 4) == 0)
			return (free(line), 0);
		free(line);
		line = NULL;
	}
	return (0);
}
