# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: denizozd <denizozd@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/21 20:35:04 by denizozd          #+#    #+#              #
#    Updated: 2024/04/21 14:24:07 by denizozd         ###   ########.fr        #
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
CFLAGS = -g -fsanitize=address
LIBFTPATH = ./libft
LIBFT = ./libft/libft.a

LDFLAGS		= -L/Users/$(USER)/.brew/opt/readline/lib -lasan
CPPFLAGS	= -I/Users/$(USER)/.brew/opt/readline/include
#LDFLAGS += -fsanitize=address

SRCS = cstm_exit.c exit_minishell.c signal_handler.c builtins.c \
		cstm_pwd.c exec.c lists_utils.c split_input.c \
		cstm_echo.c cstm_unset.c init.c main.c parser.c \
		cstm_env.c debug_utils.c lexer.c utils.c \
		cstm_cd.c cstm_export.c envp_utils.c \
		expand_var_utils.c expander.c handle_redirections.c \
		quotes_utils.c list_functions.c heredoc.c garbage_collector.c garbage_lib.c \

OBJDIR = obj
OBJS =  $(addprefix $(OBJDIR)/,$(SRCS:.c=.o))

all: $(NAME)


$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: %.c | $(OBJDIR)
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
	@rm -rf $(OBJDIR)
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
