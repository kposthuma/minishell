/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mini_loc_var.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum <kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/27 14:42:11 by kposthum      #+#    #+#                 */
/*   Updated: 2023/07/27 15:49:43 by kposthum      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include<minishell_parsing.h>

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
	ft_lstadd_back(loc_var, new);
	return (loc_var);
}

char	**check_vars(char **args, t_input *cmd)
{
	if (!args[0] || ft_strchr(args[0], '=') == NULL)
		return (args);
	if (!args[1])
		cmd->loc_var = assign_loc_var(args[0], cmd->loc_var);
	free(args[0]);
	args++;
	cmd->comm_nr--;
	return (args);
}
