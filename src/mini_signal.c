/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mini_signal.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum <kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/27 13:00:23 by kposthum      #+#    #+#                 */
/*   Updated: 2023/07/27 14:11:02 by kposthum      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include<minishell_parsing.h>

static void	signal_int(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}

// WIP
void	sigfunc(void)
{
	struct sigaction	sign;

	sign.sa_handler = signal_int;
	sigemptyset(&sign.sa_mask);
	sign.sa_flags = SA_RESTART;
	if (sigaction(SIGINT, &sign, NULL) == -1)
		ft_printf("KAAS: Signal error\n");
	if (sigaction(SIGQUIT, &sign, NULL) == -1)
		ft_printf("KAAS: Signal error\n");
}
