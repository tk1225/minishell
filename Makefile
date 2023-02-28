CC			=	cc
CFLAGS		=	-Wall -Werror -Wextra
RM			=	rm -rf
AR			=	ar rcs
NAME		=	minishell

INC			=	-I inc/ -I $(LIBFT_DIR)inc/ -I $(PRINTF_DIR)inc/ -I $(shell brew --prefix readline)/include
RDLFLAGS	=	-L $(shell brew --prefix readline)/lib -l readline

SRC_DIR		=	src/
OBJ_DIR		=	objs/
BUILT_DIR	=	builtin/
EXEC_DIR	=	exec/
MAIN_DIR	=	main/
PARSE_DIR	=	parse/
UTILS_DIR	=	utils/
LIBFT_DIR	=	$(PRINTF_DIR)libft/
PRINTF_DIR	=	$(UTILS_DIR)ft_printf/

BUILT_NAME	=	exec_cd.c exec_echo.c exec_env.c exec_exit.c exec_export.c exec_pwd.c exec_unset.c
EXEC_NAME	=	builtin_check.c builtin_set.c executer.c heredoc.c pipe.c redirection.c
MAIN_NAME	=	main.c signal.c
PARSE_NAME	=	expansion.c lexer.c parser.c syntax.c
UTILS_NAME	=	getenvs.c utils.c

OBJ_NAME	=	$(addprefix $(BUILT_DIR), $(BUILT_NAME:.c=.o))
OBJ_NAME	+=	$(addprefix $(EXEC_DIR), $(EXEC_NAME:.c=.o))
OBJ_NAME	+=	$(addprefix $(MAIN_DIR), $(MAIN_NAME:.c=.o))
OBJ_NAME	+=	$(addprefix $(PARSE_DIR), $(PARSE_NAME:.c=.o))
OBJ_NAME	+=	$(addprefix $(UTILS_DIR), $(UTILS_NAME:.c=.o))
OBJ			=	$(addprefix $(OBJ_DIR), $(OBJ_NAME))

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(UTILS_DIR) --silent
	@$(CC) -o $@ $^ $(UTILS_DIR)utils.a $(RDLFLAGS)
	@echo "##### minishell compiling finished! #####"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)$(BUILT_DIR)
	@mkdir -p $(OBJ_DIR)$(EXEC_DIR)
	@mkdir -p $(OBJ_DIR)$(MAIN_DIR)
	@mkdir -p $(OBJ_DIR)$(PARSE_DIR)
	@mkdir -p $(OBJ_DIR)$(UTILS_DIR)
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
