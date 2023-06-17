/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell_parsing.h                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum <kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/29 09:20:54 by kposthum      #+#    #+#                 */
/*   Updated: 2023/06/17 16:25:33 by kposthum      ########   odam.nl         */
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

// outfile struct
// append is false when truncating and true when appending the outfile
// for regular outfile, filename is the filename provided
// for heredoc, it is a delimiter
// for herestring, it is the herestring
typedef struct s_outf
{
	bool	append;
	char	*filename;
}	t_outf;

// infile struct
// in_type is 0 for normal infile, 1 for heredoc, 2 for herestring
// in all cases filename is the filename provided
typedef struct s_inf
{
	int		in_type;
	char	*filename;
}	t_inf;

// infile is NULL when there is no outfile
// outfile is NULL when there is no outfile

typedef struct s_commands
{
	char	**command;
	t_inf	*infile;
	t_outf	*outfile;
}	t_commands;

// main input struct
// comm_nr is the number of comamnds passed to the execute part of the shell
typedef struct s_input
{
	size_t		comm_nr;
	t_commands	**commands;
	// char		***input;
}	t_input;

char	**trim_comm_out(char **comm);
t_outf	*has_outfile(t_commands *commands);
char	**trim_comm_in(char **comm);
t_inf	*has_infile(t_commands *commands);

#endif