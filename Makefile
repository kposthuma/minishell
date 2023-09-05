# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: kposthum <kposthum@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2022/10/06 16:04:34 by kposthum      #+#    #+#                  #
#    Updated: 2023/09/05 14:54:49 by kposthum      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

CC := gcc -Wall -Werror -Wextra -g -fsanitize=address
NAME := minishell
SRCS := main.c\
		mini_signal.c\
		mini_loc_var.c\
		mini_parse.c\
		mini_parse_utils.c\
		mini_init.c\
		mini_expansion.c\
		mini_infile.c\
		mini_outfile.c\
		mini_destruction.c\
		mini_error.c\
		mini_utils.c\
		mini_testprint.c

HEADERS	:= -I ./libft/include -I ./include -I /Users/$(USER)/.brew/opt/readline/include
LIBFT := ./libft/libft.a
LIBS := -lreadline -L /Users/$(USER)/.brew/opt/readline/lib
SRCDIR := ./src
OBJDIR := ./obj
OBJS :=	$(addprefix $(OBJDIR)/,$(SRCS:.c=.o))
SRCS := $(addprefix $(SRCDIR)/,$(SRCS))

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@echo Making $(NAME)
	@$(CC) $(OBJS) $(HEADERS) $(LIBFT) $(LIBS) -o $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	@echo Compiling $<
	@$(CC) $(HEADERS) -c $< -o $@

$(LIBFT):
	@$(MAKE) -C ./libft

clean:
	@echo Removing object files $(NAME)
	@rm -f $(OBJS)
	@rm -rf $(OBJDIR)
	@$(MAKE) clean -C ./libft
	
fclean: clean
	@echo Removing $(NAME)
	@rm -f $(NAME)
	@$(MAKE) fclean -C ./libft

re:		fclean all

.PHONY: libft gnl clean fclean all re