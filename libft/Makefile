# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: remarque < remarque@student.42porto.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/27 03:53:49 by remarque          #+#    #+#              #
#    Updated: 2023/10/08 21:13:36 by remarque         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Needs header

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

NAME		=	libft.a
INCLUDE		=	../include
SRC_DIR		=	src/
OBJ_DIR		=	obj/
LIBC		=	ar rc
LIBR		=	ranlib
CC			=	cc
RM			=	rm -f
CFLAGS		=	-g -Wall -Werror -Wextra -I

#Source folders

STRING_DIR		=	string/
PRINTING_DIR	=	printing/
FT_IS_DIR		=	ft_is/
MEM_DIR			=	mem/
CONVERSION_DIR	=	conversion/
LIST_DIR		=	list/
GNL_DIR			=	get_next_line/
FTPRINTF_DIR	=	ft_printf/

#Source files

STRING		=	ft_strjoin ft_striteri ft_strlcat ft_strnstr ft_strlcpy\
				ft_strlen ft_strdup ft_strchr ft_strmapi ft_strncmp\
				ft_strrchr ft_split ft_strtrim ft_substr ft_split_str\
				ft_strdup_sted
PRINTING	=	ft_putchar_fd ft_putstr_fd ft_putendl_fd ft_putnbr_fd
FT_IS		=	ft_isalpha ft_isascii ft_isdigit ft_isalnum ft_isprint ft_iswhitespace
MEM			=	ft_memcmp ft_calloc ft_bzero ft_memchr ft_memset\
				ft_memcpy ft_memmove
CONVERSION	=	ft_tolower ft_toupper ft_itoa ft_atoi
LIST		=	ft_lstiter ft_lstdelone ft_lstmap ft_lstadd_back ft_lstlast\
				ft_lstadd_front ft_lstclear ft_lstsize ft_lstnew
GNL			=	get_next_line get_next_line_utils ft_gnl ft_gnl_reset
FTPRINTF	=	ft_printf ft_printf_utils ft_print_number ft_print_alpha ft_print_hex

SRC_FILES	=	$(addprefix $(STRING_DIR),$(STRING)) $(addprefix $(PRINTING_DIR),$(PRINTING))\
				$(addprefix $(FT_IS_DIR),$(FT_IS)) $(addprefix $(MEM_DIR),$(MEM))\
				$(addprefix $(CONVERSION_DIR),$(CONVERSION)) $(addprefix $(LIST_DIR),$(LIST))\
				$(addprefix $(GNL_DIR),$(GNL)) $(addprefix $(FTPRINTF_DIR),$(FTPRINTF))

SRCS 		= 	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJS 		= 	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))
OBJ_FILES	=	.cache_exists

all:	$(NAME)

$(NAME):	compile
	@echo "$(GREEN)Libft compiled!$(DEF_COLOR)"

compile:	$(OBJS)
	@$(LIBC) $(NAME) $(OBJS)
	@$(LIBR) $(NAME)

$(OBJ_DIR)%.o:	$(SRC_DIR)%.c | $(OBJ_FILES)
	@echo "$(YELLOW)Compiling: $< $(DEF_COLOR)"
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(OBJ_FILES):
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)$(STRING_DIR)
	@mkdir -p $(OBJ_DIR)$(PRINTING_DIR)
	@mkdir -p $(OBJ_DIR)$(FT_IS_DIR)
	@mkdir -p $(OBJ_DIR)$(MEM_DIR)
	@mkdir -p $(OBJ_DIR)$(CONVERSION_DIR)
	@mkdir -p $(OBJ_DIR)$(LIST_DIR)
	@mkdir -p $(OBJ_DIR)$(GNL_DIR)
	@mkdir -p $(OBJ_DIR)$(FTPRINTF_DIR)

clean:
	@$(RM) -r $(OBJ_DIR)
	@$(RM) $(OBJ_FILES)
	@echo "$(BLUE)Libft object files cleaned!$(DEF_COLOR)"

fclean:	clean
	@$(RM) $(NAME)
	@echo "$(CYAN)Libft library file cleaned!$(DEF_COLOR)"

re:	fclean all
	@echo "$(GREEN)Cleaned and rebuilt everything for libft!$(DEF_COLOR)"

debug:	override CFLAGS := -fsanitize=address -static-libsan $(CFLAGS)
debug:	compile
	@echo "$(GREEN)Libft compiled in debug mode!$(DEF_COLOR)"
# if stack traces look weird, add -fno-omit-frame-pointer -O1
# statically link with libasan with -static-libasan

rebug:	fclean debug
	@echo "$(GREEN)Cleaned and rebuilt everything for libft in debug mode!$(DEF_COLOR)"

#so:
#	$(CC) -nostartfiles -fPIC $(CFLAGS) $(INCLUDE) $(SRCS)
#	gcc -nostartfiles -shared -o libft.so $(OBJS)

.PHONY:	all clean fclean re debug rebug compile
