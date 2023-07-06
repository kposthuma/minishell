/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mini_error.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum <kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/20 15:08:20 by kposthum      #+#    #+#                 */
/*   Updated: 2023/07/05 14:03:55 by kposthum      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include<minishell_parsing.h>

void	syntax_error_files(char *string)
{
	ft_printf(string);
}

void	mem_err(void)
{
	ft_printf("KAAS: Memory alloaction error.\n");
}
