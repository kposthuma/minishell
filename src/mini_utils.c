/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mini_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum <kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/11 18:43:57 by kposthum      #+#    #+#                 */
/*   Updated: 2023/07/11 19:02:45 by kposthum      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include<minishell_parsing.h>

size_t	redir_len(char *line, char a)
{
	size_t	len;
	size_t	i;

	i = 0;
	len = 0;
	while (line[i])
	{
		if (line[i] == a)
		{
			while (line[i + len] == a)
				len++;
			while (ft_is_space(line[i + len]) == 0)
				len++;
			while (ft_is_space(line[i + len]) == 1)
				len++;
			return (len);
		}
		i++;
	}
	return (len);
}

char	*ft_string_snip(char *source, char	*snip)
{
	char	*left;
	char	*right;
	char	*new;

	left = ft_substr(source, 0, ft_strlen(source)
			- ft_strlen(ft_strnstr(source, snip, ft_strlen(source))));
	if (!left)
		return (NULL);
	right = ft_substr(source, ft_strlen(left) + ft_strlen(snip),
			ft_strlen(source) - ft_strlen(snip) - ft_strlen(left));
	if (!right)
		return (free(left), NULL);
	new = ft_strjoin(left, right);
	if (!new)
		return (free(left), free(right), NULL);
	return (free(left), free(right), new);
}
