<<<<<<< HEAD
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sbronwyn <sbronwyn@student.21-school.ru>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/10 18:11:01 by sbronwyn          #+#    #+#              #
#    Updated: 2021/12/13 10:58:47 by sbronwyn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = clang
CFLAGS = -Wall -Wextra -Werror -I/usr/local/Cellar/readline/8.1.1/include
LIBFLAGS= -Llibft -lft \
	-L/usr/local/Cellar/readline/8.1.1/lib -lreadline

SRC_DWEEPER = build_syntax_tree.c split_to_tokens.c execute_command.c executor_utils.c parser_memory_cleanup.c

SRC = main.c $(SRC_DWEEPER) \
	signal.c builtins.c builtins2.c

SRC_TEST = execution_checker.c $(SRC_DWEEPER)
NAME_TEST = test

LIBFT=libft/libft.a
MAKE_LIBFT=make -C libft
RM = rm -rf

all: $(NAME)

$(NAME): $(SRC:.c=.o) $(LIBFT)
	$(CC) $(CFLAGS) $(LIBFLAGS) -o $(NAME) $(SRC:.c=.o)

%.o: %.c minishell.h stree.h tokens.h Makefile
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	$(MAKE_LIBFT) clean
	$(RM) $(SRC:.c=.o)

$(LIBFT):
	$(MAKE_LIBFT) bonus

test: $(SRC_TEST:.c=.o) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME_TEST) $(SRC_TEST:.c=.o) $(LIBFLAGS)

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

.PHONY: all re clean fclean install
=======
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sbronwyn <sbronwyn@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/07 21:46:26 by stanislavko       #+#    #+#              #
#    Updated: 2021/12/09 15:26:50 by sbronwyn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = clang
CFLAGS = -Wall -Wextra -Werror
LIBFLAGS= -Llibft -lft

SRC_DWEEPER = build_syntax_tree.c split_to_tokens.c execute_command.c executor_utils.c parser_memory_cleanup.c

SRC = main.c $(SRC_DWEEPER)

SRC_TEST = execution_checker.c $(SRC_DWEEPER)
NAME_TEST = test

LIBFT=libft/libft.a
MAKE_LIBFT=make -C libft
RM = rm -rf

all: $(NAME)

$(NAME): $(SRC:.c=.o) $(LIBFT)
	$(CC) $(CFLAGS) $(LIBFLAGS) -o $(NAME) $(SRC:.c=.o)

%.o: %.c minishell.h stree.h tokens.h
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	$(MAKE_LIBFT) clean
	$(RM) $(SRC:.c=.o)

$(LIBFT):
	$(MAKE_LIBFT) bonus

test: $(SRC_TEST:.c=.o) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME_TEST) $(SRC_TEST:.c=.o) $(LIBFLAGS)

tclean:
	$(MAKE_LIBFT) fclean
	$(RM) $(SRC_TEST:.c=.o)
	$(RM) $(NAME_TEST)

fclean: clean
	$(MAKE_LIBFT) fclean
	$(RM) $(NAME)

re: fclean all

.PHONY: all re clean fclean
>>>>>>> 9b34af2 (dweeper1312_memory_bug)
