/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mini_parse_utils.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum <kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/29 16:32:06 by kposthum      #+#    #+#                 */
/*   Updated: 2023/08/31 15:30:59 by kposthum      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell_parsing.h>

void	clear_list(t_parse **head)
{
	t_parse	*temp;
	t_parse	*node;

	node = *head;
	while (node->next != NULL)
	{
		temp = node->next;
		free(node);
		node = temp;
	}
	free(head);
}

t_parse	*make_node(char *line)
{
	t_parse	*node;

	node = ft_calloc(sizeof(t_parse), 1);
	if (!node)
		return (NULL);
	node->token = line;
	node->next = NULL;
	node->last = NULL;
	return (node);
}

void	list_add_tok(t_parse **head, t_parse *token)
{
	t_parse	*final;

	if (!*head)
		head = &token;
	else
	{
		final = *head;
		while (final->next != NULL)
			final = final->next;
		token->last = final;
		final->next = token;
	}
}

t_parse	**tokenize_line(char *line)
{
	t_parse	**head;
	t_parse	*token;

	head = ft_calloc(sizeof(t_parse *), 1);
	if (!head)
		return (mem_err(), NULL);
	while (*line)
	{
		token = make_node(line);
		if (!token)
			return (mem_err(), clear_list(head), NULL);
		list_add_tok(head, token);
		if (is_bash_token(*line) == true)
			line++;
		else if (is_bash_token(*line) == false)
		{
			while (is_bash_token(*line) == false && *line)
				line++;
		}
		while (ft_isspace(*line) == 0 && *line)
			line++;
	}
	return (head);
}
