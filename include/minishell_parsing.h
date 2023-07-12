/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell_parsing.h                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum <kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/29 09:20:54 by kposthum      #+#    #+#                 */
/*   Updated: 2023/07/12 16:14:00 by kposthum      ########   odam.nl         */
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

// linked list of locally assigned variables
// useful for expansion, node 1 reserved for exit code?
// all contents are stored in the format *=* (e.g. USER=kposthum)
// typedef struct s_loc_var   REPLACED BY T_LIST
// {
// 	char				*variable;
// 	struct s_loc_var	*next;
// }	t_loc_var;

// outfile struct
// "append" is false when truncating and true when appending the outfile
// in all cases "filename" is the filename provided
typedef struct s_outf
{
	bool			append;
	char			*filename;
	struct s_outf	*next;
}	t_outf;

// infile struct
// "heredoc" is true in case of here_doc, or false for a normal infile
// for a regular outfile, "filename" is the filename
// for heredoc, it is a delimiter
typedef struct s_inf
{
	bool			heredoc;
	char			*filename;
	struct s_inf	*next;
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
	t_list		**loc_var;
}	t_input;

// mini_parse.c
bool		parse_line(char *line);
// mini_init.c
int			initialize(char *line, t_list **loc_var);
// t_commands	*make_inout(char *input);
// t_input		*make_struct(char *line);

t_outf		**check_outfile(char **input);
t_inf		**check_infile(char **input);

char		**trim_redir(char **input);
// mini_error.c
void		syntax_error(char *string, char a);
void		mem_err(void);
// mini_utils.c
size_t		redir_len(char *line, char a);
char		*ft_string_snip(char *source, char	*snip);

#endif