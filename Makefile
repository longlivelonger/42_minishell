# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sbronwyn <sbronwyn@student.21-school.ru>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/10 18:11:01 by sbronwyn          #+#    #+#              #
#    Updated: 2021/12/17 09:57:42 by sbronwyn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = clang
CFLAGS = -Wall -Wextra -Werror -I/Users/$$USER/.brew/Cellar/readline/8.1.1/include
LIBFLAGS= -Llibft -lft \
	-L/Users/$$USER/.brew/Cellar/readline/8.1.1/lib -lreadline

SRC_DWEEPER = build_syntax_tree.c split_to_tokens.c execute_command.c executor_utils.c \
		parser_memory_cleanup.c split_to_tokens_utils.c find_command.c parser_utils.c

SRC = main.c $(SRC_DWEEPER) \
	signal.c builtins.c builtins2.c env.c env_utils.c

SRC_TEST = execution_checker.c $(SRC_DWEEPER) signal.c builtins.c builtins2.c env.c env_utils.c
NAME_TEST = test

LIBFT=libft/libft.a
MAKE_LIBFT=make -C libft
RM = rm -rf

all: $(NAME)

$(NAME): $(SRC:.c=.o) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(SRC:.c=.o) $(LIBFLAGS)

%.o: %.c minishell.h stree.h tokens.h Makefile
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	$(MAKE_LIBFT) clean
	$(RM) $(SRC:.c=.o)

$(LIBFT):
	$(MAKE_LIBFT) bonus

test: $(SRC_TEST:.c=.o) $(LIBFT)
	$(CC) $(CFLAGS) -g -o $(NAME_TEST) $(SRC_TEST:.c=.o) $(LIBFLAGS)

tclean:
	$(MAKE_LIBFT) fclean
	$(RM) $(SRC_TEST:.c=.o)
	$(RM) $(NAME_TEST)

fclean: clean
	$(MAKE_LIBFT) fclean
	$(RM) $(NAME)

re: fclean all

install:
	brew install readline

home_link:
	mkdir /Users/$$USER/.brew
	ln -v -s /usr/local/Cellar /Users/$$USER/.brew/Cellar

.PHONY: all re clean fclean install
