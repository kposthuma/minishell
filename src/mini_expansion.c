/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mini_expansion.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum <kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/18 14:04:51 by kposthum      #+#    #+#                 */
/*   Updated: 2023/07/19 15:16:47 by kposthum      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include<minishell_parsing.h>

// finds the value of the variable to be replaced
char	*find_sub(t_list *var, char *name)
{
	t_loc_var	*tmp;
	char		*temp;

	temp = getenv(name + 1);
	if (temp != NULL)
		return (temp);
	while (var != NULL)
	{
		tmp = (t_loc_var *)var->cnt;
		if (ft_strncmp(tmp->variable, name + 1, ft_strlen(name)) == 0)
			return (ft_strdup(tmp->value));
		var = var->nxt;
	}
	return (ft_strdup(""));
}

// finds the name of the variable to expand and replaces it
char	*expand(char *line, size_t i, t_list *var)
{
	size_t	j;
	char	*name;
	char	*sub;

	j = i;
	while (line[j] && !ft_isspace(line[j])
		&& line[j] != '\"' && line[j] != '\'')
		j++;
	j -= i;
	name = ft_substr(line, i, j);
	sub = find_sub(var, name);
	line = ft_substr_sub(line, name, sub);
	return (line);
}

// looks for '$' to expand environmental variables,
// except in between single quotes
char	*mini_expansion(char *line, t_list **loc_var)
{
	size_t		i;
	t_list		*var;

	i = 0;
	var = *loc_var;
	while (line[i])
	{
		if (line[i] == '\'')
		{
			i++;
			while (line[i] != '\'')
				i++;
		}
		if (line[i] == '$')
		{
			line = expand(line, i, var);
			i = 0;
		}
		else
			i++;
	}
	return (line);
}
