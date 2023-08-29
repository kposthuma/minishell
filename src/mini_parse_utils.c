/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mini_parse_utils.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum <kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/29 16:32:06 by kposthum      #+#    #+#                 */
/*   Updated: 2023/08/29 17:11:40 by kposthum      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell_parsing.h>

t_parse	*make_node(char *line)
{
	t_parse	*node;

	node = ft_calloc(sizeof(t_parse *), 1);
	if (!node)
		return (mem_err(), NULL);
	node->token = line;
	node->next = NULL;
	node->last = NULL;
	return (node);
}

void	list_add_tok(t_parse **head, t_parse *token)
{
	t_parse	*final;

	if (head == NULL)
		*head = token;
	else
	{
		final = *head;
		while (final->next != NULL)
			final = final->next;
		token->last = final;
		final->next = token;
	}
}

bool	parsing(char *line)
{
	t_parse	**head;
	t_parse	*token;

	head = ft_calloc(sizeof(t_parse *), 1);
	if (!head)
		return (mem_err(), false);
	while (line != NULL)
	{
		token = make_node(line);
		if (!token)
			break ;
		list_add_tok(head, token);
		while (is_bash_token(*line) == false && line != NULL)
			line += 1;
	}
}
