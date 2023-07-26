/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_free.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum <kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/16 09:52:12 by kposthum      #+#    #+#                 */
/*   Updated: 2023/07/26 17:10:18 by kposthum      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	ft_free(char **arg)
{
	size_t	i;

	i = 0;
	while (arg && arg[i])
	{
		if (arg[i])
			free(arg[i]);
		i++;
	}
	if (arg)
		free(arg);
}
