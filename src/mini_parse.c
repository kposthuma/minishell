/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mini_parse.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum <kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/06 14:50:50 by kposthum      #+#    #+#                 */
/*   Updated: 2023/08/31 15:30:30 by kposthum      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell_parsing.h>

// mostly here so >>> or <<< doesn't work
// static char	redir_arrows(char *line, char a, size_t i)
// {
// 	size_t	j;

// 	j = 0;
// 	while (line[i] == a)
// 	{
// 		i++;
// 		j++;
// 		if (j > 2)
// 			return (line[i - 1]);
// 		if ((a == '>' && line[i] == '<') || (a == '<' && line[i] == '>')
// 			|| is_bash_token(line[i]) == true)
// 			return (line[i]);
// 		if (!line[i])
// 			return ('\n');
// 	}
// 	return (0);
// }

// char	check_redirects(char *line)
// {
// 	size_t	i;

// 	i = 0;
// 	while (line[i])
// 	{
// 		if (redir_arrows(line, '<', i) != 0)
// 			return (redir_arrows(line, '<', i));
// 		if (redir_arrows(line, '>', i) != 0)
// 			return (redir_arrows(line, '>', i));
// 		i++;
// 	}
// 	return (0);
// }

// checks if there are any unclosed quotations
size_t	check_quotes(char *line, char q1, char q2)
{
	size_t	i;
	size_t	closed;

	i = 0;
	closed = 0;
	while (line[i])
	{
		if (line[i] == q2)
		{
			i++;
			while (line[i] != '\0' && line[i] != q2)
				i++;
		}
		if (line[i] == q1)
			closed++;
		i++;
	}
	return (closed % 2);
}

bool	check_redir(t_parse *node, char a)
{
	if (node->next == NULL)
		return (false);
	if (is_bash_token(node->next->token[0]) == true
		&& node->next->token[0] != a)
		return (false);
	if (is_bash_token(node->next->token[0]) == true
		&& node->next->token[0] == a && node->last != NULL
		&& node->last->token[0] == a)
		return (false);
	return (true);
}

bool	check_pipe(t_parse *node)
{
	char	a;

	if (node->next == NULL || node->last == NULL)
		return (false);
	a = node->next->token[0];
	if (a == '|' || a == '&' || a == ';' || a == '(' || a == ')')
		return (false);
	return (true);
}

bool	check_syntax(t_parse *node)
{
	bool	check;

	if (node->token[0] == '<')
		check = check_redir(node, '<');
	else if (node->token[0] == '>')
		check = check_redir(node, '>');
	else if (node->token[0] == '|')
		check = check_pipe(node);
	else
		check = true;
	return (check);
}

bool	check_list(t_parse **head)
{
	t_parse	*node;
	bool	check;

	node = *head;
	check = true;
	while (node->next != NULL && check == true)
	{
		if (is_bash_token(node->token[0]) == true)
			check = check_syntax(node);
		node = node->next;
	}
	if (is_bash_token(node->token[0]) == true)
		check = check_syntax(node);
	return (check);
}

// looks for some syntax errors
bool	parse_line(char *line)
{
	t_parse	**head;
	bool	check;

	if (check_quotes(line, '\'', '\"') == 1
		|| check_quotes(line, '\"', '\'') == 1)
		return (syntax_error("Syntax error: Unclosed quotations.", 0), false);
	head = tokenize_line(line);
	check = check_list(head);
	clear_list(head);
	return (check);
}
