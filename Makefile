# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: remarque <remarque@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/27 03:53:49 by remarque          #+#    #+#              #
#    Updated: 2023/10/11 15:57:49 by remarque         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


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
SRC_DIR		=	src/
OBJ_DIR		=	obj/
LIBC		=	ar rc
LIBR		=	ranlib
CC			=	cc
RM			=	rm -f
CFLAGS		=	-g -Wall -Werror -Wextra -I $(INCLUDE)
VG			=	valgrind --leak-check=full -s --show-leak-kinds=all \
				--suppressions=readline_supression --log-file=leaks.log
LIB			=	-lreadline
# Libs are always after objects in the compilation
# If you put them before, it won't compile

#Source folders
# To add a new source folder, you need to add it here, in the source files, in the 
# SRC_FILES list and in the $(OBJ_FILES): rule

SRC_ROOT_DIR		=	
PARSING_DIR			=	parsing/
UTILS_DIR			=	utils/


#Source files

SRC_ROOT	=	minishell
PARSING		=	parser
UTILS		=	echo pwd utils


SRC_FILES	=	$(addprefix $(SRC_ROOT_DIR),$(SRC_ROOT)) $(addprefix $(PARSING_DIR),$(PARSING))\
				$(addprefix $(UTILS_DIR),$(UTILS)) 

SRCS 		= 	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJS 		= 	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))
OBJ_FILES	=	.cache_exists

all:	$(NAME)

$(NAME):	compile
	@echo "$(GREEN)Minishell compiled!$(DEF_COLOR)"

compile:	$(OBJS) libft.a
	@$(CC) $(CFLAGS) $(OBJS) $(LIB) -o $(NAME)

libft.a:
	@make $(DEBUG) -C $(LIBFT)
	@cp libft/libft.a .

$(OBJ_DIR)%.o:	$(SRC_DIR)%.c | $(OBJ_FILES)
	@echo "$(YELLOW)Compiling: $< $(DEF_COLOR)"
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_FILES):
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)$(SRC_ROOT_DIR)
	@mkdir -p $(OBJ_DIR)$(PARSING_DIR)
	@mkdir -p $(OBJ_DIR)$(UTILS_DIR)

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

debug:	override CFLAGS := -fsanitize=address -static-libasan $(CFLAGS)
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