# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sbronwyn <sbronwyn@student.21-school.ru>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/10 18:11:01 by sbronwyn          #+#    #+#              #
#    Updated: 2021/12/10 18:11:03 by sbronwyn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc
CFLAGS = -Wall -Wextra -Werror
LIBFLAGS= -Llibft -lft -lreadline

SRC = main.c

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

.PHONY: all re clean fclean