/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell_parsing.h                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum <kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/29 09:20:54 by kposthum      #+#    #+#                 */
/*   Updated: 2023/09/13 14:31:50 by kposthum      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_PARSING_H
# define MINISHELL_PARSING_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <signal.h>
# include <dirent.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <libft.h>

// locally assigned variable struct
// useful for expansion, node 1 reserved for exit code?
typedef struct s_loc_var
{
	char	*variable;
	char	*value;
}	t_loc_var;

// outfile struct
// "append" is false when truncating and true when appending the outfile
// in all cases "filename" is the filename provided
typedef struct s_outf
{
	bool			append;
	char			*filename;
}	t_outf;

// infile struct
// "heredoc" is true in case of here_doc, or false for a normal infile
// for a regular outfile, "filename" is the filename
// for heredoc, it is a delimiter
typedef struct s_inf
{
	bool			heredoc;
	char			*filename;
}	t_inf;

// infile contains NULL when there is no outfile
// outfile contains NULL when there is no outfile
typedef struct s_commands
{
	char	*command;
	char	**args;
	t_list	**infiles;
	t_list	**outfiles;
}	t_commands;

// main input struct
// comm_nr is the number of comamnds passed to the execute part of the shell
typedef struct s_input
{
	size_t		comm_nr;
	t_commands	**commands;
	t_list		**loc_var;
}	t_input;

// parsing struct
typedef struct s_parse
{
	char			*token;
	struct s_parse	*next;
	struct s_parse	*last;
}	t_parse;

// main.c

// mini_signal.h
void		sigfunc(void);

// mini_loc_var.c
void		clear_loc_var(t_list **loc_var);
t_list		**init_loc_var(void);
void		set_status(t_list **loc_var, int status);
char		**check_vars(char **args, t_input *cmd);

// mini_parse.c
bool		parse_line(char *line);

// mini_parse_utils.c
void		clear_list(t_parse **head);
t_parse		**tokenize_line(char *line);

// mini_init.c
int			initialize(char *line, t_list **loc_var);

// mini_expansion.c
char		*mini_expansion(char *line, t_list **loc_var);

//mini_infile.c
char		*check_infile(t_commands *command, char *input);

// mini_outfile.c
char		*check_outfile(t_commands *command, char *input);

// mini_destruction.c
void		free_command_struct(t_commands *command);
void		free_cmd(t_input *cmd, size_t i);
void		destroy_cmd(t_input *cmd);

// mini_error.c
void		syntax_error(char *string, char a);
void		mem_err(void);

// mini_utils.c
bool		check_quotes(char *line);
char		*ft_strchr_quotes(char *s, char c);
size_t		redir_len(char *line, char a);
bool		is_bash_tok(char a);

// mini_utils_string.c
char		*ft_trim_quotes(char *s);
char		**ft_trim_quotes_double(char **src);
char		*ft_string_snip(char *source, char	*snip);
char		*ft_strjointhree(char *str1, char *str2, char *str3);
char		*ft_substr_sub(char *src, char *str1, char *str2);


void		print_all_the_shit(t_input *cmd);

#endif