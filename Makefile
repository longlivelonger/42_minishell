# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sbronwyn <sbronwyn@student.21-school.ru>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/10 18:11:01 by sbronwyn          #+#    #+#              #
#    Updated: 2021/12/11 14:56:17 by sbronwyn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc
CFLAGS = -Wall -Wextra -Werror -I/usr/local/Cellar/readline/8.1.1/include
LIBFLAGS= -Llibft -lft \
	-L/usr/local/Cellar/readline/8.1.1/lib -lreadline

SRC = main.c \
	signal.c

LIBFT=libft/libft.a
MAKE_LIBFT=make -C libft
RM = rm -rf

all: $(NAME)

$(NAME): $(SRC:.c=.o) $(LIBFT)
	$(CC) $(CFLAGS) $(LIBFLAGS) -o $(NAME) $(SRC:.c=.o)

%.o: %.c minishell.h Makefile
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	$(MAKE_LIBFT) clean
	$(RM) $(SRC:.c=.o)

$(LIBFT):
	$(MAKE_LIBFT) bonus

fclean: clean
	$(MAKE_LIBFT) fclean
	$(RM) $(NAME)

re: fclean all

install:
	brew install readline

.PHONY: all re clean fclean install