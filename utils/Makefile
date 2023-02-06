# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atito <atito@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/04 21:16:46 by atito             #+#    #+#              #
#    Updated: 2023/02/04 22:21:09 by atito            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			=	cc
CFLAGS		=	-Wall -Werror -Wextra
RM			=	rm -rf
AR			=	ar rcs
NAME		=	utils.a

PRINTF_DIR	=	ft_printf/
GNL_DIR		=	get_next_line/
OBJ_DIR		=	objs/

all:
	make -C $(PRINTF_DIR)
	make -C $(GNL_DIR)
	@mkdir -p $(OBJ_DIR)
	@cd $(OBJ_DIR);ar -x ../$(PRINTF_DIR)libftprintf.a
	@cd $(OBJ_DIR);ar -x ../$(GNL_DIR)gnl.a
	$(AR) $(NAME) $(OBJ_DIR)*.o

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
