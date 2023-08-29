/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstlast_bonus.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum <kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/16 14:04:10 by kposthum      #+#    #+#                 */
/*   Updated: 2023/08/29 13:51:21 by kposthum      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*pnt;

	pnt = lst;
	if (!lst)
		return (0);
	while (lst->nxt != 0 && lst->nxt != pnt)
		lst = lst->nxt;
	return (lst);
}
