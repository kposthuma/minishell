/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mini_checker.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum <kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/06 14:50:50 by kposthum      #+#    #+#                 */
/*   Updated: 2023/07/06 15:38:26 by kposthum      ########   odam.nl         */
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

char	check_redirects(char *line)
{
	
}

void	parse_line(char *line)
{
	if (check_quotes(line, '\'') == 1 || check_quotes(line, '\"') == 1)
		return (syntax_error("Syntax error: Unclosed quotations.", 0));
	if (check_redirects(line) > 0)
		return (syntax_error("Syntax error near unexpected token", 
				check_redirects(line)));
}
