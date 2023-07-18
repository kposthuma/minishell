/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mini_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum <kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/11 18:43:57 by kposthum      #+#    #+#                 */
/*   Updated: 2023/07/18 16:19:12 by kposthum      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include<minishell_parsing.h>

char	*ft_strchr_quotes(char *s, char c)
{
	size_t			i;
	size_t			j;

	i = 0;
	j = ft_strlen(s) + 1;
	while (i < j)
	{
		if (s[i] == '\"')
		{
			i++;
			while (s[i] != '\"')
				i++;
		}
		if (s[i] == '\'')
		{
			i++;
			while (s[i] != '\'')
				i++;
		}
		if (s[i] == c)
			return (&s[i]);
		i++;
	}
	return (NULL);
}

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
			while (ft_isspace(line[i + len]) == 1)
				len++;
			while (is_bash_token(line[i + len]) == false && line[i + len])
				len++;
			return (len);
		}
		i++;
	}
	return (len);
}

//removes a part (snip) of a string and joins the remainder together
char	*ft_string_snip(char *source, char	*snip)
{
	char	*left;
	char	*right;
	char	*new;

	left = ft_substr(source, 0, ft_strlen(source)
			- ft_strlen(ft_strnstr(source, snip, ft_strlen(source))));
	if (!left)
		return (free(source), NULL);
	right = ft_substr(source, ft_strlen(left) + ft_strlen(snip),
			ft_strlen(source) - ft_strlen(snip) - ft_strlen(left));
	if (!right)
		return (free(source), free(left), NULL);
	new = ft_strjoin(left, right);
	if (!new)
		return (free(source), free(left), free(right), NULL);
	return (free(source), free(left), free(right), new);
}

// strjoin, but for three strings
char	*ft_strjointhree(char *str1, char *str2, char *str3)
{
	char	*joined;
	int		i[3];

	i[0] = ft_strlen(str1);
	i[1] = ft_strlen(str2);
	i[2] = ft_strlen(str3);
	joined = ft_calloc((i[0] + i[1] + i[2] + 1), sizeof(char));
	if (!joined)
		return (NULL);
	ft_strlcpy(joined, str1, (i[0] + 1));
	ft_strlcat(joined, str2, (i[0] + i[1] + 1));
	ft_strlcat(joined, str3, (i[0] + i[1] + i[2] + 1));
	return (joined);
}

// replaces the first occurance of substring str1 in string src with string str2
char	*ft_substr_sub(char *src, char *str1, char *str2)
{
	char	*left;
	char	*right;
	char	*new;

	left = ft_substr(src, 0, ft_strlen(src)
			- ft_strlen(ft_strnstr(src, str1, ft_strlen(src))));
	if (!left)
		return (free(src), NULL);
	right = ft_substr(src, ft_strlen(left) + ft_strlen(str1),
			ft_strlen(src) - ft_strlen(str1) - ft_strlen(left));
	if (!right)
		return (free(src), free(left), NULL);
	new = ft_strjointhree(left, str2, right);
	if (!new)
		return (free(src), free(left), free(right), NULL);
	return (free(src), free(left), free(right), new);
}
