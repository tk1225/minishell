NAME		=	minishell
FLAGS		=	-Wall -Wextra -Werror
INC			=	-Iinc/ -I$(LIB_DIR)
RDLFLAGS	=	-lreadline

SRC_NAME	=	minishell.c parser.c executer.c lexer.c utils.c
BUILT_NAME	=	exec_cat.c exec_echo.c exec_env.c exec_exit.c exec_export.c exec_pwd.c exec_unset.c

OBJ_NAME	=	$(SRC_NAME:.c=.o)
OBJ_NAME	+=	$(addprefix $(BUILT_DIR), $(BUILT_NAME:.c=.o))
OBJ			=	$(addprefix $(OBJ_DIR), $(OBJ_NAME))

LIB_DIR		=	libft/
SRC_DIR		=	src/
OBJ_DIR		=	objs/
BUILT_DIR	=	builtin/

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(LIB_DIR) --silent
	@gcc -o $@ $^ -L $(LIB_DIR) -lft $(RDLFLAGS)
	@echo "##### minishell compiling finished! #####"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)$(BUILT_DIR)
	@echo "##### Creating" [ $@ ] " #####"
	@gcc $(FLAGS) -o $@ -c $^ $(INC)

clean:
	@make -C $(LIB_DIR) clean --silent
	@rm -rf $(OBJ_DIR)
	@echo "##### Removed object files #####"

fclean: clean
	@make -C $(LIB_DIR) fclean --silent
	@rm -rf $(NAME)
	@echo "##### Removed binary files #####"

re: fclean all

.PHONY: all clean fclean re
