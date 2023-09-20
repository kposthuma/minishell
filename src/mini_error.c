/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mini_error.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum <kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/20 15:08:20 by kposthum      #+#    #+#                 */
/*   Updated: 2023/09/20 14:20:44 by kposthum      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell_parsing.h>

// hihghly sophisticated error message
void	syntax_error(char *reason, char a)
{
	ft_putstr_fd("KAAS: syntax error", STDERR_FILENO);
	ft_putstr_fd(reason, STDERR_FILENO);
	if (a != 0 && a != '\n')
		ft_putchar_fd(a, STDERR_FILENO);
	else if (a == '\n')
		ft_putstr_fd("newline", STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
}

// in case of malloc fail
void	mem_err(void)
{
	ft_putstr_fd("KAAS: Memory alloaction error.\n", 2);
}
