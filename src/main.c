/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum <kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/29 09:22:23 by kposthum      #+#    #+#                 */
/*   Updated: 2023/06/08 11:54:33 by kposthum      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include<minishell_parsing.h>

void	sigfunc(int signum)
{
	printf("aapjes, %i", signum);
	exit(signum);
}

t_outf	*has_outfile(t_commands *cmd)
{
	t_outf	*outfile;
	size_t	i;

	i = strofstrlen(cmd->commands[cmd->comm_nr - 1]) - 2;
	if (ft_strncmp(cmd->commands[cmd->comm_nr - 1][i], ">>", 3) != 0 &&
		ft_strncmp(cmd->commands[cmd->comm_nr - 1][i], ">", 2) != 0)
		return (NULL);
	outfile = ft_calloc(1, sizeof(t_inf));
	if (ft_strncmp(cmd->commands[cmd->comm_nr - 1][i], ">>", 3) == 0)
		outfile->append = true;
	else
		outfile->append = false;
	outfile->filename = ft_strdup(cmd->commands[cmd->comm_nr - 1][i + 1]);
	return (outfile);
}

t_inf	*has_infile(t_commands *cmd)
{
	t_inf	*infile;

	if (ft_strncmp(cmd->commands[0][0], "<<", 3) != 0 &&
		ft_strncmp(cmd->commands[0][0], "<", 2) != 0)
		return (NULL);
	infile = ft_calloc(1, sizeof(t_inf));
	if (ft_strncmp(cmd->commands[0][0], "<<", 3) == 0)
		infile->heredoc = true;
	else
		infile->heredoc = false;
	infile->filename = ft_strdup(cmd->commands[0][1]);
	return (infile);
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
	cmd->infile = has_infile(cmd);
	cmd->outfile = has_outfile(cmd);
	i = 0;
	printf("nr of commands: %lu\n", cmd->comm_nr);
	while (cmd->commands[i])
	{
		print_charpp(cmd->commands[i]);
		printf("end of command nr %lu\n\n", i + 1);
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
