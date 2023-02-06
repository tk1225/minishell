# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atito <atito@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/17 18:50:34 by atito             #+#    #+#              #
#    Updated: 2023/02/04 21:11:33 by atito            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			=	cc
CFLAGS		=	-Wall -Werror -Wextra
RM			=	rm -rf
AR			=	ar rcs
NAME		=	gnl.a

INC			=	-I inc/

SRC_DIR		=	src/
OBJ_DIR		=	objs/

SRC_NAME	=	get_next_line.c get_next_line_utils.c

OBJ		=	$(addprefix $(OBJ_DIR)/, $(SRC_NAME:.c=.o))

all:	$(NAME)

$(NAME):	$(OBJ)
	$(AR) $@ $^

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -o $@ -c $^ $(INC)

clean:
	$(RM) $(OBJ_DIR)

fclean:	clean
	$(RM) $(NAME)

re:	fclean all

.PHONY:	all clean fclean re
