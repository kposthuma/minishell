/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atol.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum <kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/28 14:17:30 by kposthum      #+#    #+#                 */
/*   Updated: 2023/08/29 13:53:40 by kposthum      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_atol(const char *str)
{
	long	i;
	int		j;

	i = 0;
	j = 1;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == 43 || *str == 45)
	{
		if (*str == 45)
			j = j * -1;
		str++;
	}
	while (*str >= 48 && *str <= 57)
	{
		i = 10 * i + (*str - 48);
		str++;
	}
	i = i * j;
	return (i);
}
