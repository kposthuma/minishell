/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mini_expansion.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum <kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/18 14:04:51 by kposthum      #+#    #+#                 */
/*   Updated: 2023/07/27 15:55:01 by kposthum      ########   odam.nl         */
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
	while (line[j] && ft_isspace(line[j])
		&& line[j] != '\"' && line[j] != '\'')
		j++;
	j -= i;
	name = ft_substr(line, i, j);
	sub = find_sub(var, name);
	if (!name || !sub)
		return (free(name), free(sub), NULL);
	sub = ft_trim_quotes(sub);
	line = ft_substr_sub(line, name, sub);
	free(name);
	free(sub);
	return (line);
}

// looks for '$' to expand environmental variables,
// except in between single quotes
char	*mini_expansion(char *line, t_list **loc_var)
{
	size_t		i;
	t_list		*var;
	char		*str;

	i = 0;
	var = *loc_var;
	str = ft_strdup(line);
	if (!str)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '\'')
		{
			i++;
			while (str[i] != '\'')
				i++;
		}
		if (str[i] == '$')
			str = expand(str, i, var);
		if (!str)
			return (NULL);
		else
			i++;
	}
	return (str);
}
