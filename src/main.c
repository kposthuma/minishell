/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum <kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/29 09:22:23 by kposthum      #+#    #+#                 */
/*   Updated: 2023/05/29 10:49:50 by kposthum      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include<minishell_parsing.h>

int	main(void)
{
	char	*input;

	while (true)
	{
		write(STDOUT_FILENO, "Kaas% ", 7);
		input = get_next_line(STDIN_FILENO);
		if (ft_strncmp(input, "exit\n", 5) == 0)
			return (free(input), 0);
		printf("input = %s", input);
		free(input);
	}
}
