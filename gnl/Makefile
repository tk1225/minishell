# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: takuokam <takuokam@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/31 18:31:13 by takuokam          #+#    #+#              #
#    Updated: 2023/02/05 17:55:54 by takuokam         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := gnl.a
CC		:= cc
CFLAGS	:= -Wall -Wextra -Werror
SRCS	:= get_next_line.c get_next_line_utils.c
OBJS	:= get_next_line.o get_next_line_utils.o

all: $(NAME)

$(NAME):$(OBJS)
	ar rcs $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY:	all clean fclean re
