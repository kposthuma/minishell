/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mini_parse_utils.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum <kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/29 16:32:06 by kposthum      #+#    #+#                 */
/*   Updated: 2023/08/31 16:59:45 by kposthum      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell_parsing.h>

void	clear_list(t_parse **head)
{
	t_parse	*temp;
	t_parse	*curr;

	temp = *head;
	while (temp != NULL)
	{
		curr = temp;
		temp = temp->next;
		free(curr);
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

t_parse	*list_final(t_parse *list)
{
	if (!list)
		return (NULL);
	while (list->next != NULL)
		list = list->next;
	return (list);
}

void	list_add_tok(t_parse **head, t_parse *token)
{
	t_parse	*final;

	if (!*head)
		*head = token;
	else
	{
		final = list_final(*head);
		final->next = token;
		token->last = final;
	}
}

t_parse	**tokenize_line(char *line)
{
	t_parse	**head;
	t_parse	*token;

	head = ft_calloc(sizeof(t_parse *), 1);
	if (!head)
		return (mem_err(), NULL);
	while (*line != '\0')
	{
		token = make_node(line);
		if (!token)
			return (mem_err(), clear_list(head), NULL);
		list_add_tok(head, token);
		if (is_bash_tok(*line) == true)
			line++;
		else if (is_bash_tok(*line) == false)
		{
			while (*line && is_bash_tok(*line) == false && isspace(*line) == 0)
				line++;
		}
		while (*line != '\0' && ft_isspace(*line) == 1)
			line++;
	}
	return (head);
}
