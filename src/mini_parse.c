/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mini_parse.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum <kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/06 14:50:50 by kposthum      #+#    #+#                 */
/*   Updated: 2023/09/05 16:11:01 by kposthum      ########   odam.nl         */
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

bool	check_redir(t_parse *node, char a)
{
	if (node->next == NULL)
		return (false);
	if (is_bash_tok(node->next->token[0]) == true
		&& node->next->token[0] != a)
		return (false);
	if (is_bash_tok(node->next->token[0]) == true
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
		if (is_bash_tok(node->token[0]) == true)
			check = check_syntax(node);
		node = node->next;
	}
	if (is_bash_tok(node->token[0]) == true)
		check = check_syntax(node);
	return (check);
}

// looks for some syntax errors
bool	parse_line(char *line)
{
	t_parse	**head;
	bool	check;

	if (check_quotes(line) == false)
		return (syntax_error("Syntax error: Unclosed quotations.", 0), false);
	head = tokenize_line(line);
	check = check_list(head);
	// check = true;
	clear_list(head);
	return (check);
}
