/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mini_trim.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum <kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/04 16:25:27 by kposthum      #+#    #+#                 */
/*   Updated: 2023/07/04 16:50:12 by kposthum      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include<minishell_parsing.h>

static size_t	get_arg_len(char **input)
{
	size_t	len;
	size_t	i;

	len = strofstrlen(input);
	i = 0;
	while (input[i])
	{
		if (input[i][0] == '<' || input[i][0] == '>')
		{
			len--;
			if (input[i][ft_strlen(input[i] - 1)] != '<'
				|| input[i][ft_strlen(input[i] - 1)] != '>')
				len--;
		}
		i++;
	}
	return (len);
}

static char	**make_args(char **input, size_t arg_len)
{
	char	**args;
	size_t	i;
	size_t	j;

	args = ft_calloc(arg_len + 1, sizeof(char *));
	i = 0;
	j = 0;
	while (i < arg_len)
	{
		while (input[j][0] == '<' || input[j][0] == '>')
			j++;
		while ((input[j][0] == '<' && input[j][ft_strlen(input[j] - 1)] == '<')
			|| input[j][0] == '>' && input[j][ft_strlen(input[j] - 1)] == '>')
			j += 2;
		args[i] = ft_strdup(input[j]);
		i++;
		j++;
	}
}

char	**trim_redir(char **input)
{
	char	**args;
	size_t	arg_len;

	arg_len = get_arg_len(input);
	args = make_args(input, arg_len);
	return (args);
}
