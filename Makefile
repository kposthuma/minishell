# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: kposthum <kposthum@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2022/10/06 16:04:34 by kposthum      #+#    #+#                  #
#    Updated: 2023/07/12 13:53:23 by kposthum      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

CC := gcc -Wall -Werror -Wextra
NAME := minishell
SRCS := main.c\
		mini_parse.c\
		mini_init.c\
		mini_infile.c\
		mini_outfile.c\
		mini_error.c\
		mini_trim.c\
		mini_utils.c

HEADERS	:= -I ./libft/include -I ./include -I /Users/$(USER)/.brew/opt/readline/include
LIBFT := ./libft/libft.a
LIBS := -lreadline
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