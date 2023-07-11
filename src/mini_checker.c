/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mini_checker.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum <kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/06 14:50:50 by kposthum      #+#    #+#                 */
/*   Updated: 2023/07/11 17:21:08 by kposthum      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include<minishell_parsing.h>

size_t	check_quotes(char *line, char q)
{
	size_t	i;
	size_t	closed;

	i = 0;
	closed = 0;
	while (line[i])
	{
		if (line[i] == q)
			closed++;
		i++;
	}
	return (closed % 2);
}

bool	is_bash_token(char a)
{
	if (a == '|' || a == '&' || a == ';'
		|| a == '(' || a == ')')
		return (true);
	return (false);
}

char	redir_arrows(char *line, char a, size_t i)
{
	size_t	j;

	j = 0;
	while (line[i] == a)
	{
		i++;
		j++;
		if (j > 1 || is_bash_token(line[i]) == true)
			return (line[i]);
		if ((a == '>' && line[i] == '<') || (a == '<' && line[i] == '>'))
			return (line[i]);
		if (!line[i])
			return ('\n');
	}
	return (0);
}

char	check_redirects(char *line)
{
	size_t	i;

	i = 0;
	while (line[i])
	{
		if (redir_arrows(line, '<', i) != 0)
			return (redir_arrows(line, '<', i));
		if (redir_arrows(line, '>', i) != 0)
			return (redir_arrows(line, '>', i));
		i++;
	}
	return (0);
}

void	parse_line(char *line)
{
	// t_input		*cmd;

	if (check_quotes(line, '\'') == 1 || check_quotes(line, '\"') == 1)
		syntax_error("Syntax error: Unclosed quotations.", 0);
	else if (check_redirects(line) > 0)
		syntax_error("Syntax error near unexpected token", 
			check_redirects(line));
	// else
	// 	cmd = make_struct(line);
}
