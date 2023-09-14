/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mini_parse.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum <kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/06 14:50:50 by kposthum      #+#    #+#                 */
/*   Updated: 2023/09/14 17:28:49 by kposthum      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell_parsing.h>

bool	check_redir(t_parse *node, char a)
{
	if (node->next == NULL)
		return (syntax_error("near unexpected token", '\n'), false);
	if (is_bash_tok(node->next->token[0]) == true
		&& node->next->token[0] != a)
		return (syntax_error("near unexpected token",
				node->next->token[0]), false);
	if (is_bash_tok(node->next->token[0]) == true
		&& node->next->token[0] == a && node->last != NULL
		&& node->last->token[0] == a)
		return (syntax_error("near unexpected token",
				node->next->token[0]), false);
	if (node->next->token[0] == a && ft_isspace(node->token[1]) == 1)
		return (syntax_error("near unexpected token",
				node->next->token[0]), false);
	return (true);
}

bool	check_pipe(t_parse *node)
{
	char	a;

	if (node->next == NULL || node->last == NULL)
		return (syntax_error("near unexpected token", '\n'), false);
	a = node->next->token[0];
	if (a == '|' || a == '&' || a == ';' || a == '(' || a == ')')
		return (syntax_error("near unexpected token",
				node->next->token[0]), false);
	return (true);
}

bool	check_syntax(t_parse *node)
{
	if (node->token[0] == '<')
		return (check_redir(node, '<'));
	else if (node->token[0] == '>')
		return (check_redir(node, '>'));
	else if (node->token[0] == '|')
		return (check_pipe(node));
	return (true);
}

bool	check_list(t_parse **head)
{
	t_parse	*node;
	bool	check;

	node = *head;
	check = true;
	while (node != NULL && check == true)
	{
		if (is_bash_tok(node->token[0]) == true)
			check = check_syntax(node);
		node = node->next;
	}
	return (check);
}

// looks for some syntax errors
bool	parse_line(char *line)
{
	t_parse	**head;
	bool	check;

	if (check_quotes(line) == false)
		return (syntax_error(": Unclosed quotations.", 0), false);
	head = tokenize_line(line);
	check = check_list(head);
	clear_list(head);
	return (check);
}
