/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_charcount.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum <kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/01 13:02:59 by kposthum      #+#    #+#                 */
/*   Updated: 2023/07/12 14:00:32 by kposthum      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"
// counts the amount char c occurs in string str
size_t	ft_charcount(const char *str, char c)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == c)
			j++;
		i++;
	}
	return (j);
}
