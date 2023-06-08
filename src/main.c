/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum <kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/29 09:22:23 by kposthum      #+#    #+#                 */
/*   Updated: 2023/06/08 11:02:46 by kposthum      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include<minishell_parsing.h>

void	sigfunc(int signum)
{
	printf("aapjes, %i", signum);
	exit(signum);
}

t_commands	*parse_line(char *line)
{
	t_commands	*cmd;
	char		**temp;
	size_t		i;

	i = 0;
	cmd = ft_calloc(1, sizeof(t_commands));
	cmd->comm_nr = ft_charcount(line, '|') + 1;
	cmd->commands = ft_calloc(cmd->comm_nr + 1, sizeof(char **));
	temp = ft_split(line, '|');
	while (i < cmd->comm_nr)
	{
		cmd->commands[i] = ft_split_quotes(temp[i], ' ');
		i++;
	}
	ft_free(temp);
	i = 0;
	while (cmd->commands[i])
	{
		print_charpp(cmd->commands[i]);
		printf("end of command\n\n");
		i++;
	}
	return (cmd);
}

int	main(void)
{
	static char	*line;
	t_commands	*cmd;

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
}
