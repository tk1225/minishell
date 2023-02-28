CC			=	cc
CFLAGS		=	-Wall -Werror -Wextra
RM			=	rm -rf
AR			=	ar rcs
NAME		=	minishell

INC			=	-I inc/ -I $(LIBFT_DIR)inc/ -I $(shell brew --prefix readline)/include
RDLFLAGS	=	-L $(shell brew --prefix readline)/lib -lreadline

SRC_DIR		=	src/
OBJ_DIR		=	objs/
BUILT_DIR	=	builtin/
EXEC_DIR	=	exec/
MAIN_DIR	=	main/
PARSE_DIR	=	parse/
UTILS_DIR	=	utils/
LIBFT_DIR	=	libft/

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
	@make -C $(LIBFT_DIR) --silent
	@$(CC) $(RDLFLAGS) -o $@ $^ $(LIBFT_DIR)libft.a
	@echo "##### minishell compiling finished! #####"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)$(BUILT_DIR)
	@mkdir -p $(OBJ_DIR)$(EXEC_DIR)
	@mkdir -p $(OBJ_DIR)$(MAIN_DIR)
	@mkdir -p $(OBJ_DIR)$(PARSE_DIR)
	@mkdir -p $(OBJ_DIR)$(UTILS_DIR)
	@echo "##### Creating" [ $@ ] " #####"
	@$(CC) $(CFLAGS) $(INC) -o $@ -c $^

clean:
	@make clean -C $(LIBFT_DIR) --silent
	@$(RM) $(OBJ_DIR)
	@echo "##### Removed object files #####"

fclean: clean
	@make fclean -C $(LIBFT_DIR) --silent
	@$(RM) $(NAME)
	@echo "##### Removed binary files #####"

re: fclean all

.PHONY: all clean fclean re
