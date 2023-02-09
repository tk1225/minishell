CC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra
RM			=	rm -rf
AR			=	ar rcs
NAME		=	minishell

INC			=	-I inc/ -I $(LIBFT_DIR)inc/ -I $(PRINTF_DIR)inc/ -I $(GNL_DIR)inc/
RDLFLAGS	=	-lreadline

SRC_DIR		=	src/
BUILT_DIR	=	builtin/
OBJ_DIR		=	objs/
UTILS_DIR	=	utils/
LIBFT_DIR	=	$(PRINTF_DIR)libft/
PRINTF_DIR	=	$(UTILS_DIR)ft_printf/
GNL_DIR		=	$(UTILS_DIR)get_next_line/

SRC_NAME	=	main.c parser.c executer.c lexer.c utils.c expansion.c
BUILT_NAME	=	exec_cd.c exec_echo.c exec_env.c exec_exit.c\
				exec_export.c exec_pwd.c exec_unset.c exec_set.c

OBJ_NAME	=	$(SRC_NAME:.c=.o)
OBJ_NAME	+=	$(addprefix $(BUILT_DIR), $(BUILT_NAME:.c=.o))
OBJ			=	$(addprefix $(OBJ_DIR), $(OBJ_NAME))

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(UTILS_DIR) --silent
	@$(CC) -o $@ $^ $(UTILS_DIR)utils.a $(RDLFLAGS)
	@echo "##### minishell compiling finished! #####"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)$(BUILT_DIR)
	@echo "##### Creating" [ $@ ] " #####"
	@$(CC) $(CFLAGS) -o $@ -c $^ $(INC)

clean:
	@make clean -C $(UTILS_DIR) --silent
	@$(RM) $(OBJ_DIR)
	@echo "##### Removed object files #####"

fclean: clean
	@make fclean -C $(UTILS_DIR) --silent
	@$(RM) $(NAME)
	@echo "##### Removed binary files #####"

re: fclean all

.PHONY: all clean fclean re
