/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum <kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/29 09:22:23 by kposthum      #+#    #+#                 */
/*   Updated: 2023/09/05 14:51:37 by kposthum      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell_parsing.h>

// void	f(void)
// {
// 	system("leaks minishell");
// }

int	main(void)
{
	static char	*line;
	t_list		**loc_var;

	sigfunc();
	loc_var = init_loc_var();
	if (!loc_var)
		return (mem_err(), 1);
	rl_replace_line("KAAS% ", 0);
	while (true)
	{
		line = readline("KAAS% ");
		if (!line)
			break ;
		if (ft_strncmp(line, "exit", 4) == 0)
			return (free(line), clear_loc_var(loc_var), 0);
		if (line && *line)
		{
			add_history(line);
			set_status(loc_var, initialize(line, loc_var));
		}
		free(line);
		line = NULL;
	}
	clear_loc_var(loc_var);
	return (printf("\nexit\n"), 0);
}

// for testing expansion

// int	main(void)
// {
// 	static char	*line;
// 	t_list		**loc_var;

// 	loc_var = init_loc_var();
// 	while (true)
// 	{
// 		line = readline("line1: ");
// 		printf("line 1: %s\n", line);
// 		if (ft_strncmp(line, "exit", 4) == 0)
// 			exit (0);
// 		line = mini_expansion(line, loc_var);
// 		printf("line 2: %s\n", line);
// 		free(line);
// 	}
// 	exit (0);
// }

// for testing string snip

// int	main(void)
// {
// 	static char	*line1;
// 	static char	*line2;
// 	t_list		**loc_var;

// 	signal(SIGINT, sigfunc);
// 	loc_var = init_loc_var();
// 	if (!loc_var)
// 		return (mem_err(), 1);
// 	while (true)
// 	{
// 		line1 = readline("line1% ");
// 		if (!line1)
// 			return (printf("\nexit\n"), 0);
// 		if (line1 && *line1)
// 			add_history(line1);
// 		line2 = readline("line2% ");
// 		line1 = ft_string_snip(line1, line2);
// 		printf("line 1 after: %s\n", line1);
// 		free(line1);
// 		free(line2);
// 		line1 = NULL;
// 		line2 = NULL;
// 	}
// 	return (0);
// }
