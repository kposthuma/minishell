/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum <kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/29 09:22:23 by kposthum      #+#    #+#                 */
/*   Updated: 2023/06/17 16:06:57 by kposthum      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include<minishell_parsing.h>

void	sigfunc(int signum)
{
	printf("aapjes, %i", signum);
	exit(signum);
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
	temp = ft_split(line, '|');
	while (i < cmd->comm_nr)
	{
		cmd->commands[i]->command = ft_split_quotes(temp[i], ' ');
		i++;
	}
	ft_free(temp);
	printf("nr of input: %lu\n", cmd->comm_nr);
	cmd->commands[i]->infile = has_infile(cmd->commands[i]);
	if (cmd->commands[i]->infile != NULL)
		cmd->commands[i]->command = trim_comm_in(cmd->commands[i]->command);
	cmd->commands[i]->outfile = has_outfile(cmd->commands[i]);
	if (cmd->commands[i]->outfile != NULL)
		cmd->commands[i]->command = trim_comm_out(cmd->commands[i]->command);
	i = 0;
	while (cmd->commands[i]->command)
	{
		print_charpp(cmd->commands[i]->command);
		printf("end of command nr %lu\n\n", i + 1);
		i++;
	}
	if (cmd->commands[i]->infile != NULL)
		printf("name infile: %s\n", cmd->commands[i]->infile->filename);
	if (cmd->commands[i]->outfile != NULL)
		printf("name outfile: %s\n", cmd->commands[i]->outfile->filename);
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
