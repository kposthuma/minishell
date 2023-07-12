/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum <kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/29 09:22:23 by kposthum      #+#    #+#                 */
/*   Updated: 2023/07/12 16:12:59 by kposthum      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include<minishell_parsing.h>

void	sigfunc(int signum)
{
	printf("aapjes, %i", signum);
	exit(signum);
}

t_list	**init_loc_var(void)
{
	t_list	**loc_var;
	t_list	*status;

	loc_var = ft_calloc(sizeof(t_list *), 1);
	status = ft_lstnew((void *)"?=0");
	ft_lstadd_front(loc_var, status);
	return (loc_var);
}

int	main(void)
{
	static char	*line;
	t_list		**loc_var;

	signal(SIGINT, sigfunc);
	loc_var = init_loc_var();
	while (true)
	{
		line = readline("KAAS% ");
		if (!line)
			return (printf("\nexit\n"), 0);
		if (line && *line)
			add_history(line);
		if (parse_line(line) == true)
			initialize(line, loc_var); // returns exit status?
		if (ft_strncmp(line, "exit", 4) == 0)
			return (free(line), 0);
		free(line);
		line = NULL;
	}
	return (0);
}
