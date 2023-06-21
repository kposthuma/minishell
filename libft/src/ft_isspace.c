/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isspace.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum <kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/04 12:59:35 by kposthum      #+#    #+#                 */
/*   Updated: 2023/06/21 14:57:50 by kposthum      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

int	ft_isspace(int c)
{
	if (!ft_strchr("\t\n\v\f\r ", c))
		return (0);
	else
		return (1);
}
