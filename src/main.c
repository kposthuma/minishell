/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum <kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/29 09:22:23 by kposthum      #+#    #+#                 */
/*   Updated: 2023/07/19 13:48:37 by kposthum      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include<minishell_parsing.h>

void	sigfunc(int signum)
{
	printf("aapjes, %i", signum);
}

t_list	**init_loc_var(void)
{
	t_list		**loc_var;
	t_list		*new;
	t_loc_var	*status;

	loc_var = ft_calloc(sizeof(t_list *), 1);
	status = ft_calloc(sizeof(t_loc_var *), 1);
	if (!loc_var || !status)
		return (free(loc_var), free(status), NULL);
	status->variable = ft_strdup("?");
	status->value = ft_strdup("0");
	if (!status->variable || !status->value)
		return (free(status->variable), free(status->value),
			free(status), free(loc_var), NULL);
	new = ft_lstnew((void *)status);
	if (!new)
		return (free(status->variable), free(status->value),
			free(status), free(loc_var), NULL);
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

	signal(SIGINT, sigfunc);
	loc_var = init_loc_var();
	if (!loc_var)
		return (mem_err(), 1);
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
