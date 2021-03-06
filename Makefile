# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sbronwyn <sbronwyn@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/10 18:11:01 by sbronwyn          #+#    #+#              #
#    Updated: 2021/12/22 15:12:49 by sbronwyn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = clang
CFLAGS = -Wall -Wextra -Werror -I/Users/$$USER/.brew/Cellar/readline/8.1.1/include
LIBFLAGS= -Llibft -lft \
	-L/Users/$$USER/.brew/Cellar/readline/8.1.1/lib -lreadline

SRC_DWEEPER = build_syntax_tree.c split_to_tokens.c execute_command.c executor_utils.c \
		parser_memory_cleanup.c split_to_tokens_utils.c find_command.c parser_utils.c executor_utils_2.c executor_utils_3.c

SRC = main.c $(SRC_DWEEPER) \
	signal.c builtins.c builtins2.c builtins3.c builtins4.c \
	env.c env_utils.c env_array.c global.c

SRC_TEST = execution_checker.c $(SRC_DWEEPER) signal.c builtins.c builtins2.c env.c env_utils.c
NAME_TEST = test

HEADERS=minishell.h syntax_tree.h tokens.h

LIBFT=libft/libft.a
MAKE_LIBFT=make -C libft
RM = rm -rf

all: $(NAME)

$(NAME): $(SRC:.c=.o) $(LIBFT) $(HEADERS)
	$(CC) $(CFLAGS) -o $(NAME) $(SRC:.c=.o) $(LIBFLAGS)

%.o: %.c $(HEADERS)
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
