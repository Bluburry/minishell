NAME	= minishell
	# $(CC) $(CFLAGS) $(TARGET) -o $(NAME)

# flags
CC		= cc
CFLAGS	= -Wall -Werror -Wextra -g -fsanitize=address -lreadline
RM		= rm -rf
AR		= ar -rcs
VG		= valgrind --leak-check=full -s --show-leak-kinds=all --suppressions=readline_supression

# folders
LIBFT	= libft
INC		= include
OUTPUT	= out
SRC		= src
REQ		= $(addprefix $(SRC)/, utils) $(addprefix $(SRC)/, parsing) \
_FLDRS	= $(SRC) $(REQ)

VPATH	= $(_FLDRS)

# files
LIB		= $(addprefix $(LIBFT)/, lib)
MAIN	= $(addprefix $(SRC)/, minishell.c)
_FILES	= #parser utils

OBJS	= $(_FILES:%=%.o)
TARGET	= $(addprefix $(OUTPUT)/, $(OBJS))


all : $(NAME)

$(NAME) : $(OUTPUT) $(TARGET)
	make -C $(LIBFT)
	$(CC) $(CFLAGS) $(MAIN) $(TARGET) $(LIB) -o $(NAME) -I $(INC)

$(OUTPUT)/%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OUTPUT) :
	mkdir -p $(OUTPUT)


clean : 
	make clean -C $(LIBFT)
	$(RM) $(OUTPUT)

fclean : 
	make fclean -C $(LIBFT)
	$(RM) $(OUTPUT)
	$(RM) $(NAME)

re : fclean all

leaks :
	$(VG) --log-file=leaks.log ./minishell

.SILENT :

.PHONY : all, clean, fclean, re, leaks
