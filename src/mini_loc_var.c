/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mini_loc_var.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum <kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/27 14:42:11 by kposthum      #+#    #+#                 */
/*   Updated: 2023/09/19 15:16:44 by kposthum      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell_parsing.h>

void	clear_loc_var(t_list **loc_var)
{
	t_loc_var	*current;
	t_list		*temp1;
	t_list		*temp2;

	temp1 = *loc_var;
	while (temp1 != NULL)
	{
		temp2 = temp1;
		current = (t_loc_var *)temp2->cnt;
		temp1 = temp1->nxt;
		free(current->variable);
		free(current->value);
		free(current);
		free(temp2);
	}
	*loc_var = NULL;
	free(*loc_var);
	free(loc_var);
}

//initializes a linked list of locally stored variables
// and sets the initial status to 0
t_list	**init_loc_var(void)
{
	t_list		**loc_var;
	t_list		*new;
	t_loc_var	*status;

	loc_var = ft_calloc(sizeof(t_list *), 1);
	status = ft_calloc(sizeof(t_loc_var), 1);
	if (!loc_var || !status)
		return (free(loc_var), free(status), NULL);
	status->variable = ft_strdup("?");
	status->value = ft_strdup("0");
	if (!status->variable || !status->value)
		return (free(status->variable), free(status->value),
			free(status), free(loc_var), NULL);
	new = ft_lstnew((void *)status);
	if (!new)
		return (free(status->variable), free(status->value),
			free(status), free(loc_var), NULL);
	ft_lstadd_front(loc_var, new);
	return (loc_var);
}

// execute part should retrun the exit status, gets saved here
void	set_status(t_list **loc_var, int status)
{
	t_list		*new;
	t_loc_var	*num;

	new = *loc_var;
	num = (t_loc_var *)new->cnt;
	free(num->value);
	num->value = ft_itoa(status);
}

// searches for an occurance of var in loc_var and removes it
void	remove_duplicate(t_list **loc_var, char *var)
{
	t_loc_var	*temp1;
	t_list		*temp2;
	t_list		*temp3;

	temp2 = *loc_var;
	while (temp2 != NULL)
	{
		if (temp2->nxt != NULL)
		{
			temp1 = (t_loc_var *)temp2->nxt->cnt;
			if (ft_strncmp(temp1->variable, var, ft_strlen(var)) == 0)
			{
				temp3 = temp2->nxt;
				temp2->nxt = temp2->nxt->nxt;
				free(temp1->value);
				free(temp1->variable);
				free(temp1);
				free(temp3);
			}
		}
		temp2 = temp2->nxt;
	}
}

// assign a local variable to the list 
// TODO -if variable exists in env, export in stead of add to list
t_list	**assign_loc_var(char *src, t_list **loc_var)
{
	t_list		*new;
	t_loc_var	*var;
	size_t		len;

	var = ft_calloc(1, sizeof(t_loc_var));
	if (!var)
		return (mem_err(), loc_var);
	var->value = ft_strdup(ft_strchr(src, '=') + 1);
	len = 0;
	while (src[len] != '=')
		len++;
	var->variable = ft_substr(src, 0, len);
	new = ft_lstnew((void *)var);
	if (!var->value || !var->variable || !new)
		return (free(var->value), free(var->variable),
			free(var), free(new), mem_err(), loc_var);
	remove_duplicate(loc_var, var->variable);
	ft_lstadd_back(loc_var, new);
	return (loc_var);
}

// allows user to store variables locally with "variable=value"
// ingnores such inputs if other inputs are also present
char	**check_vars(char **args, t_input *cmd)
{
	char	*temp;
	size_t	i;

	if (!args[0] || ft_strchr(args[0], '=') == NULL)
		return (args);
	if (!args[1] && cmd->comm_nr == 1)
		cmd->loc_var = assign_loc_var(args[0], cmd->loc_var);
	i = 0;
	temp = args[0];
	while (args[i])
	{
		args[i] = args[i + 1];
		i++;
	}
	free(temp);
	return (args);
}
