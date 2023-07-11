/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell_parsing.h                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum <kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/29 09:20:54 by kposthum      #+#    #+#                 */
/*   Updated: 2023/07/11 17:23:46 by kposthum      ########   odam.nl         */
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
// "append" is false when truncating and true when appending the outfile
// in all cases "filename" is the filename provided
typedef struct s_outf
{
	bool	append;
	char	*filename;
}	t_outf;

// infile struct
// "heredoc" is true in case of here_doc, or false for a normal infile
// for a regular outfile, "filename" is the filename
// for heredoc, it is a delimiter
typedef struct s_inf
{
	bool	heredoc;
	char	*filename;
}	t_inf;

// infile contains NULL when there is no outfile
// outfile contains NULL when there is no outfile
typedef struct s_commands
{
	char	*command;
	char	**args;
	t_inf	**infiles;
	t_outf	**outfiles;
}	t_commands;

// main input struct
// comm_nr is the number of comamnds passed to the execute part of the shell
typedef struct s_input
{
	size_t		comm_nr;
	t_commands	**commands;
}	t_input;

typedef struct s_loc_var
{
	char				*variable;
	struct s_loc_var	*next;
}	t_loc_var;

t_commands	*make_inout(char *input);
t_input		*make_struct(char *line);

t_outf		**check_outfile(char **input);
t_inf		**check_infile(char **input);

char		**trim_redir(char **input);

void		syntax_error(char *string, char a);
void		mem_err(void);

void		parse_line(char *line);

#endif