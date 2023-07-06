/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum <kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/29 09:22:23 by kposthum      #+#    #+#                 */
/*   Updated: 2023/07/06 12:51:31 by kposthum      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include<minishell_parsing.h>

void	sigfunc(int signum)
{
	printf("aapjes, %i", signum);
	exit(signum);
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
			return (printf("\nexit\n"), 0);
		if (line && *line)
			add_history(line);
		cmd = parse_line(line);
		// else
		// 	mini_execution(cmd)
		if (ft_strncmp(line, "exit", 4) == 0)
			return (free(line), 0);
		free(line);
		line = NULL;
	}
	return (0);
}
