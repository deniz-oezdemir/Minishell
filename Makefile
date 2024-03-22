# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ecarlier <ecarlier@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/21 20:35:04 by denizozd          #+#    #+#              #
#    Updated: 2024/03/22 22:30:23 by ecarlier         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

G = "\033[32m"
Y = "\033[33m"
B = "\033[34m"
X = "\033[0m"
UP = "\033[A"
CUT = "\033[K"

NAME = minishell
CC = cc
#CFLAGS = -Wall -Werror -Wextra #commented out to not silence all unused vars
LIBFTPATH = ./libft
LIBFT = ./libft/libft.a
LDFLAGS		= -L/Users/$(USER)/.brew/opt/readline/lib
CPPFLAGS	= -I/Users/$(USER)/.brew/opt/readline/include

SRCS = cstm_exit.c end.c signal_handler.c builtins.c \
		cstm_pwd.c exec.c lists_utils.c split_input.c \
		cstm_echo.c cstm_unset.c init.c main.c parser.c \
		cstm_env.c debug_utils.c lexer.c utils.c envp_utils.c \
		expand_var_utils.c expander.c


OBJS = $(SRCS:.c=.o)

all: $(NAME)

%.o: %.c
	@echo $(Y)Compiling$(X)
	@$(CC) $(CFLAGS) -c -o $@ $<
	@printf $(UP)$(CUT)

$(LIBFT):
	@echo $(Y)"Compiling	[libft]"$(X)
	@make -C $(LIBFTPATH) > /dev/null
	@echo $(G)"Created		[libft]"$(X)

$(NAME): $(LIBFT) $(OBJS)
	@echo $(Y)"Compiling	"[$(SRCS)]$(X)
	@echo $(G)"Created		"[$(SRCS)]$(X)
	@echo $(Y)"Compiling	"[$(NAME)]$(X)
	@$(CC) $(OBJS) $(LDFLAGS) $(CPPFLAGS) -lreadline -L$(LIBFTPATH) -lft -o $(NAME)
	@echo $(G)"Created		"[$(NAME)]$(X)

clean:
	@echo $(B)"Removing	objectfiles"$(X)
	@rm -f $(OBJS)
	@cd $(LIBFTPATH) && make clean > /dev/null
	@echo $(G)"Removed		objectfiles"$(X)

fclean: clean
	@echo $(B)"Removing	executable"$(X)
	@rm -f $(NAME)
	@echo $(G)"Removed		executable"$(X)
	@echo $(B)"Removing	library"$(X)
	@cd $(LIBFTPATH) && make fclean > /dev/null
	@echo $(G)"Removed		library"$(X)

re: fclean all
