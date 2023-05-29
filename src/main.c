/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum <kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/29 09:22:23 by kposthum      #+#    #+#                 */
/*   Updated: 2023/05/29 14:42:37 by kposthum      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include<minishell_parsing.h>

int	main(void)
{
	char	*line;

	while (true)
	{
		line = readline("KAAS% ");
		if (!line || ft_strncmp(line, "exit", 4) == 0)
			return (free(line), 0);
		else
		{
			printf("line = %s\n", line);
			free(line);
		}
	}
}
