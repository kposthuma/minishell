/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mini_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum <kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/11 18:43:57 by kposthum      #+#    #+#                 */
/*   Updated: 2023/09/10 14:59:11 by kposthum      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell_parsing.h>

// checks if there are any unclosed quotations
bool	check_quotes(char *line)
{
	size_t	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\'')
		{
			i++;
			while (line[i] != '\0' && line[i] != '\'')
				i++;
		}
		if (line[i] == '\"')
		{
			i++;
			while (line[i] != '\0' && line[i] != '\"')
				i++;
		}
		if (line[i] == '\0')
			return (false);
		i++;
	}
	return (true);
}

// ft_strchr, but skips over quotation marks
char	*ft_strchr_quotes(char *s, char c)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = ft_strlen(s);
	while (i < j)
	{
		if (s[i] == '\"')
		{
			i++;
			while (s[i] && s[i] != '\"')
				i++;
		}
		if (s[i] == '\'')
		{
			i++;
			while (s[i] && s[i] != '\'')
				i++;
		}
		if (s[i] && s[i] == c)
			return (&s[i]);
		i++;
	}
	return (NULL);
}

// detemines the length of a string line starting at position len
// up to and including delimiter a, assuming line[len] == a
static size_t	ft_quotelen(char *line, char a, size_t len)
{
	len++;
	while (line[len] != a)
		len++;
	return (len + 1);
}

// determines the lenght of filename for in or outfiles
size_t	redir_len(char *line, char a)
{
	size_t	len;
	size_t	i;

	i = 0;
	len = 0;
	while (line[i] && line[i] != a)
		i++;
	if (line[i] == a)
	{
		while (line[i + len] == a)
			len++;
		while (ft_isspace(line[i + len]) == 1)
			len++;
		if (line[i + len] == '\"')
			return (ft_quotelen(line, '\"', len + i) - i);
		if (line[i + len] == '\'')
			return (ft_quotelen(line, '\'', len + i) - i);
		while (is_bash_tok(line[i + len]) == false && line[i + len]
			&& ft_isspace(line[i + len]) == 0)
			len++;
		return (len);
	}
	return (len);
}

// because certain tokens cannot be used in certain instances
bool	is_bash_tok(char a)
{
	if (a == '|' || a == '&' || a == ';'
		|| a == '(' || a == ')' || a == '>' || a == '<')
		return (true);
	return (false);
}
