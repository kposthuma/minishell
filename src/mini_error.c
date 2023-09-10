/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mini_error.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum <kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/20 15:08:20 by kposthum      #+#    #+#                 */
/*   Updated: 2023/08/29 13:49:26 by kposthum      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell_parsing.h>

// hihghly sophisticated error message
void	syntax_error(char *reason, char a)
{
	ft_printf("KAAS: syntax error ");
	if (a != 0 && a != '\n')
		ft_printf("%s \'%c\'\n", reason, a);
	else if (a == '\n')
		ft_printf("%s \'newline\'\n", reason);
	else
		ft_printf("%s\n", reason);
}

// in case of malloc fail
void	mem_err(void)
{
	ft_printf("KAAS: Memory alloaction error.\n");
}
