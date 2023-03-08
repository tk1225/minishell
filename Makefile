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
GNL_DIR		=	gnl/
LIBFT_DIR	=	libft/

BUILT_NAME	=	export_utils1.c export_utils2.c exec_cd.c exec_echo.c exec_env.c exec_exit.c exec_export.c exec_pwd.c exec_unset.c
EXEC_NAME	=	builtin_check.c builtin_set.c executer.c heredoc.c pipe.c pipe_utils.c redirection.c
MAIN_NAME	=	main.c signal_h.c signal_p.c signal_s.c
PARSE_NAME	=	expansion_utils.c expansion.c lexer_utils.c lexer.c parser.c syntax.c
UTILS_NAME	=	ch_dir.c free.c get_env.c utils.c wrapper.c
GNL_NAME	=	get_next_line.c get_next_line_utils.c

OBJ_NAME	=	$(addprefix $(BUILT_DIR), $(BUILT_NAME:.c=.o))
OBJ_NAME	+=	$(addprefix $(EXEC_DIR), $(EXEC_NAME:.c=.o))
OBJ_NAME	+=	$(addprefix $(MAIN_DIR), $(MAIN_NAME:.c=.o))
OBJ_NAME	+=	$(addprefix $(PARSE_DIR), $(PARSE_NAME:.c=.o))
OBJ_NAME	+=	$(addprefix $(UTILS_DIR), $(UTILS_NAME:.c=.o))
OBJ_NAME	+=	$(addprefix $(GNL_DIR), $(GNL_NAME:.c=.o))
OBJ			=	$(addprefix $(OBJ_DIR), $(OBJ_NAME))

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(LIBFT_DIR) --silent
	@$(CC) -o $@ $^ $(LIBFT_DIR)libft.a $(RDLFLAGS)
	@echo "##### minishell compiling finished! #####"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)$(BUILT_DIR)
	@mkdir -p $(OBJ_DIR)$(EXEC_DIR)
	@mkdir -p $(OBJ_DIR)$(MAIN_DIR)
	@mkdir -p $(OBJ_DIR)$(PARSE_DIR)
	@mkdir -p $(OBJ_DIR)$(UTILS_DIR)
	@mkdir -p $(OBJ_DIR)$(GNL_DIR)
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
