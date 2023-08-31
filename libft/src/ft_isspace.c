/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isspace.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum <kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/04 12:59:35 by kposthum      #+#    #+#                 */
/*   Updated: 2023/08/30 15:17:52 by kposthum      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// due to fuckup, will return 1 if not a space and 0 otherwhise
int	ft_isspace(int c)
{
	if (!ft_strchr("\t\n\v\f\r ", c))
		return (1);
	else
		return (0);
}
