# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sbronwyn <sbronwyn@student.21-school.ru    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/07 21:46:26 by stanislavko       #+#    #+#              #
#    Updated: 2021/11/02 13:26:05 by sbronwyn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRC = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c \
	ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c \
	ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c \
	ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c \
	ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c \
	ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c \
	ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c

SRC_BONUS = ft_lstadd_back_bonus.c ft_lstadd_front_bonus.c \
	ft_lstclear_bonus.c ft_lstdelone_bonus.c ft_lstiter_bonus.c \
	ft_lstlast_bonus.c ft_lstmap_bonus.c ft_lstnew_bonus.c ft_lstsize_bonus.c

AR = ar rcs
RM = rm -rf

all: $(NAME)

$(NAME): $(SRC:.c=.o)
	$(AR) $(NAME) $(SRC:.c=.o)

%.o: %.c libft.h
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	$(RM) $(SRC:.c=.o) $(SRC_BONUS:.c=.o)

fclean: clean
	$(RM) $(NAME)

re: fclean all

bonus: $(NAME) $(SRC_BONUS:.c=.o)
	$(AR) $(NAME) $(SRC_BONUS:.c=.o)

.PHONY: all re clean fclean bonus