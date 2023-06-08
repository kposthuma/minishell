/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell_parsing.h                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum <kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/29 09:20:54 by kposthum      #+#    #+#                 */
/*   Updated: 2023/06/08 11:44:01 by kposthum      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_PARSING_H
# define MINISHELL_PARSING_H

# include<stdlib.h>
# include<unistd.h>
# include<stdio.h>
# include<fcntl.h>
# include<signal.h>
# include<dirent.h>
# include<termios.h>
# include<curses.h>
# include<term.h>
# include<sys/wait.h>
# include<sys/stat.h>
# include<sys/ioctl.h>
# include<readline/readline.h>
# include<readline/history.h>
# include<libft.h>

typedef struct s_outf
{
	bool	append;
	char	*filename;
}	t_outf;

typedef struct s_inf
{
	bool	heredoc;
	char	*filename;
}	t_inf;

typedef struct s_commands
{
	size_t	comm_nr;
	char	***commands;
	t_inf	*infile;
	t_outf	*outfile;
}	t_commands;

#endif