/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mini_error.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum <kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/20 15:08:20 by kposthum      #+#    #+#                 */
/*   Updated: 2023/07/11 17:18:15 by kposthum      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include<minishell_parsing.h>

void	syntax_error(char *string, char a)
{
	if (a != 0 && a != '\n')
		ft_printf("%s \'%c\'\n", string, a);
	else if (a == '\n')
		ft_printf("%s \'newline\'\n", string);
	else
		ft_printf("%s\n", string);
}

void	mem_err(void)
{
	ft_printf("KAAS: Memory alloaction error.\n");
}
