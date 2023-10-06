NAME	= lib

# flags
CC		= cc
CFLAGS	= -Wall -Wextra -Werror
RM		= rm -rf
AR		= ar -rcs


# folders
SRCS	= .
LIBFT	= libft
FOLDERS	= printf gnl $(addprefix  $(LIBFT)/, checkers) $(addprefix  $(LIBFT)/, lists) \
	$(addprefix  $(LIBFT)/, memory) $(addprefix  $(LIBFT)/, putfd) \
	$(addprefix  $(LIBFT)/, string) $(addprefix  $(LIBFT)/, misc)
VPATH	= $(FOLDERS)
OUTPUT	= out


# files
_PRINTF	= ft_printf ft_utils ft_printhexa ft_printptr 
_GNL	= get_next_line get_next_line_bonus get_next_line_utils
_LIBFT	= ft_atoi ft_bzero ft_calloc ft_isalnum ft_isalpha \
	ft_isascii ft_isdigit ft_isprint ft_itoa ft_memchr \
	ft_memcmp ft_memcpy ft_memmove ft_memset ft_putchar_fd \
	ft_putendl_fd ft_putnbr_fd ft_putstr_fd ft_split \
	ft_strlcat ft_strchr ft_strlcpy ft_strncmp ft_strdup \
	ft_striteri ft_strjoin ft_strlen ft_strmapi ft_strnstr \
	ft_strrchr ft_substr ft_strtrim ft_tolower ft_toupper \
	ft_lstnew ft_lstadd_front ft_lstsize ft_lstlast \
	ft_lstadd_back ft_lstdelone ft_lstclear \
	ft_check_alnum ft_cmpstr

_FILES	= $(_PRINTF) $(_GNL) $(_LIBFT)
OBJS	= $(_FILES:%=%.o)
TARGET	= $(addprefix $(OUTPUT)/, $(OBJS))


all : $(NAME)

$(NAME) : $(OUTPUT) $(TARGET)
	@$(AR) $(NAME) $(TARGET)

$(OUTPUT)/%.o : %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(OUTPUT) : 
	@mkdir -p $(OUTPUT)

clean : 
	@$(RM) $(OUTPUT)

fclean : clean
	@$(RM) $(NAME)

re: fclean all

.SILENT:

.PHONY: all, clean, fclean, re
