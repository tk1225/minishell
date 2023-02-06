# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atito <atito@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/22 13:49:24 by atito             #+#    #+#              #
#    Updated: 2022/10/30 17:17:08 by atito            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror
RM			=	rm -rf
AR			=	ar rcs
NAME		=	libftprintf.a

INC			=	-I inc/ -I $(LIBFT_DIR)inc/

SRC_DIR		=	src/
OBJ_DIR		=	objs/
LIBFT_DIR	=	libft/

SRC_NAME	=	ft_printf.c ft_prints.c ft_hex.c ft_str_upper.c ft_uitoa.c

OBJ		=	$(addprefix $(OBJ_DIR)/, $(SRC_NAME:.c=.o))

all:	$(NAME)

$(NAME):	$(OBJ)
	make -C $(LIBFT_DIR)
	cp $(LIBFT_DIR)/libft.a .
	mv libft.a $@
	$(AR) $@ $^

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -o $@ -c $^ $(INC)

clean:
	$(RM) $(OBJ_DIR)
	make clean -C libft

fclean:	clean
	$(RM) $(NAME)
	make fclean -C libft

re:	fclean all

.PHONY:	all clean fclean re
