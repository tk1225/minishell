# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atito <atito@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/04 21:16:46 by atito             #+#    #+#              #
#    Updated: 2023/02/14 20:11:33 by atito            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			=	cc
CFLAGS		=	-Wall -Werror -Wextra
RM			=	rm -rf
AR			=	ar rcs
NAME		=	utils.a

PRINTF_DIR	=	ft_printf/

all:
	make -C $(PRINTF_DIR)
	cp $(PRINTF_DIR)libftprintf.a .
	mv libftprintf.a $(NAME)

clean:
	$(RM) $(OBJ_DIR)
	make clean -C $(PRINTF_DIR)
	make clean -C $(GNL_DIR)

fclean:	clean
	$(RM) $(NAME)
	make fclean -C $(PRINTF_DIR)
	make fclean -C $(GNL_DIR)

re:	fclean all

.PHONY:	all clean fclean re bonus
