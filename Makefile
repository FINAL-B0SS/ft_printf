# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maljean <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/06/06 03:01:42 by maljean           #+#    #+#              #
#    Updated: 2018/06/06 03:08:22 by maljean          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
NAME = libftprintf.a
CFLAGS = -Wall -Wextra -Werror
SRCS = apply.c cast.c conv1.c conv2.c ft_printf.c parse.c strings1.c strings2.c
OBJS = apply.o cast.o conv1.o conv2.o ft_printf.o parse.o strings1.o strings2.o

all: $(NAME)

$(NAME):
	$(CC) $(CFLAGS) -c $(SRCS)
	ar rc $(NAME) $(OBJS)
	ranlib $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
