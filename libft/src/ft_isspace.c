/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isspace.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum <kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/04 12:59:35 by kposthum      #+#    #+#                 */
/*   Updated: 2023/07/13 15:04:19 by kposthum      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

int	ft_isspace(int c)
{
	if (!ft_strchr("\t\n\v\f\r ", c))
		return (1);
	else
		return (0);
}
