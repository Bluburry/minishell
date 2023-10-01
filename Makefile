NAME	= minishell
	# $(CC) $(CFLAGS) $(TARGET) -o $(NAME)

# flags
CC		= cc
CFLAGS	= -Wall -Werror -Wextra -g 
RM		= rm -rf
AR		= ar -rcs

# folders
LIBFT	= lib
INC		= include
OUTPUT	= out
SRC		= src
REQ		= $(addprefix $(SRC)/, utils) $(addprefix $(SRC)/, parsing)
_FLDRS	= $(SRC) $(REQ)

VPATH	= $(_FLDRS)

# files
LIB		= $(addprefix $(LIBFT), lib)
MAIN	= $(addprefix $(SRC)/, minishell.c)
UTILS	= 
PARSE	=

_FILES	= $(UTILS) $(PARSE) 
OBJS	= $(_FILES:%=%.o)
TARGET	= $(addprefix $(OUTPUT)/, $(OBJS))


all : $(NAME)

$(NAME) : $(OUTPUT) $(TARGET)
	Make -C $(LIBFT)
	$(CC) $(CFLAGS) $(MAIN) $(TARGET) $(LIB) -o $(NAME) -I $(INC)

$(OUTPUT)/%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OUTPUT) :
	mkdir -p $(OUTPUT)


clean : 
	Make clean -C $(LIBFT)
	$(RM) $(OUTPUT)

fclean : 
	Make fclean -C $(LIBFT)
	$(RM) $(OUTPUT)
	$(RM) $(NAME)

re : fclean all


.SILENT :

.PHONY : all, clean, fclean, re
