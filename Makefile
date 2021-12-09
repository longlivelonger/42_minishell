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

CC = gcc
CFLAGS = -Wall -Wextra -Werror
LIBFLAGS= -Llibft -lft

SRC = main.c

LIBFT=libft/libft.a
MAKE_LIBFT=make -C libft
RM = rm -rf

all: $(NAME)

$(NAME): $(SRC:.c=.o) $(LIBFT)
	$(CC) $(CFLAGS) $(LIBFLAGS) -o $(NAME) $(SRC:.c=.o)

%.o: %.c minishell.h
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