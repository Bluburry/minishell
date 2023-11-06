#Colors
DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

#Basic definitions
NAME		=	minishell
INCLUDE		=	include
LIBFT		=	libft
SRC_DIR		=	src/
OBJ_DIR		=	obj/
LIBC		=	ar rc
LIBR		=	ranlib
CC			=	cc
RM			=	rm -f
CFLAGS		=	-g -Wall -Werror -Wextra -I $(INCLUDE)
VG			=	valgrind --leak-check=full -s --show-leak-kinds=all \
				--suppressions=readline_supression --log-file=leaks.log
LIB			=	-lreadline -L. -lft
# Libs are always after objects in the compilation
# If you put them before, it won't compile

# To add a new source folder, add it to DIRS
DIRS	=	parsing utils lexer struct_handling change_directory
P_DIRS	=	$(addprefix $(SRC_DIR), $(DIRS))
vpath %.c src $(P_DIRS)

#Source files
# To add a new source file, add it to SRCS
SRCS	=	minishell lexer lexer_utils split_tokens split_quote_tokens split_char_tokens \
			split_inout_tokens merge_tokens_cleanup space_tokens_cleanup var_to_value \
			expand_var_tokens echo pwd utils alter_env clear_env find_env_var start_env_vars \
      		print_env print_export cd change_path relative_path
OBJS 	= 	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRCS)))

OBJ_FILES	=	.cache_exists

all:	$(NAME)

$(NAME):	compile
	@echo "$(GREEN)Minishell compiled!$(DEF_COLOR)"

compile:	$(OBJS) libft.a
	@$(CC) $(CFLAGS) $(OBJS) $(LIB) -o $(NAME)

libft.a:
	@make $(DEBUG) -C $(LIBFT)
	@cp libft/libft.a .

$(OBJ_DIR)%.o:	%.c | $(OBJ_FILES)
	@echo "$(YELLOW)Compiling: $< $(DEF_COLOR)"
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_FILES):
	@mkdir -p $(OBJ_DIR)

clean:
	@$(RM) -r $(OBJ_DIR)
	@$(RM) $(OBJ_FILES)
	@make fclean -C $(LIBFT)
	@echo "$(BLUE)Minishell object files cleaned!$(DEF_COLOR)"

fclean:	clean
	@$(RM) $(NAME)
	@echo "$(CYAN)Minishell file cleaned!$(DEF_COLOR)"
	@$(RM) libft.a
	@echo "$(CYAN)Root libft library file cleaned!$(DEF_COLOR)"

re:	fclean all
	@echo "$(GREEN)Cleaned and rebuilt everything for Minishell!$(DEF_COLOR)"

debug:	override CFLAGS := -fsanitize=address -static-libsan $(CFLAGS)
debug:	compile
	@echo "$(GREEN)Minishell compiled in debug mode!$(DEF_COLOR)"
# if stack traces look weird, add -fno-omit-frame-pointer -O1
# statically link with libasan with -static-libasan

rebug:	fclean debug
	@echo "$(GREEN)Cleaned and rebuilt everything for Minishell in debug mode!$(DEF_COLOR)"

leaks: ./minishell
	$(VG) ./minishell

#so:
#	$(CC) -nostartfiles -fPIC $(CFLAGS) $(INCLUDE) $(SRCS)
#	gcc -nostartfiles -shared -o libft.so $(OBJS)

.PHONY:	all clean fclean re debug rebug compile leaks

