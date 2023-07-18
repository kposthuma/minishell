/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum <kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/29 09:22:23 by kposthum      #+#    #+#                 */
/*   Updated: 2023/07/18 15:02:44 by kposthum      ########   odam.nl         */
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
	t_list		**loc_var;
	t_list		*new;
	t_loc_var	*status;

	loc_var = ft_calloc(sizeof(t_list *), 1);
	status = ft_calloc(sizeof(t_loc_var *), 1);
	status->variable = ft_strdup("?");
	status->value = ft_strdup("0");
	new = ft_lstnew((void *)status);
	ft_lstadd_front(loc_var, new);
	return (loc_var);
}

void	set_status(t_list **loc_var, int status)
{
	t_list		*new;
	t_loc_var	*num;

	new = *loc_var;
	num = (t_loc_var *)new->cnt;
	free(num->value);
	num->value = ft_itoa(status);
}

int	main(void)
{
	static char	*line;
	t_list		**loc_var;
	int			status;

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
			set_status(loc_var, initialize(line, loc_var)); // returns exit status?
		if (ft_strncmp(line, "exit", 4) == 0)
			return (free(line), 0);
		free(line);
		line = NULL;
	}
	return (0);
}
