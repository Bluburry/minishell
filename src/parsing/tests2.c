#include "../../include/libft.h"
#include <term.h>
#include <fcntl.h>
#include <signal.h>
#include <dirent.h>
#include <curses.h>
#include <termios.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/resource.h>
#include <readline/readline.h>
#include <readline/history.h>

/* 
size_t	ft_strlen(const char *s)
{
	int	i;

	if (s == NULL)
		return (0);
	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

static int	is_in_set(const char c, const char *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	i;
	size_t	start;
	size_t	end;

	start = 0;
	if (!s1 || !set)
		return (0);
	while (is_in_set(s1[start], set) && s1[start])
		start++;
	end = ft_strlen(s1);
	while (is_in_set(s1[end - 1], set) && end > start)
		end--;
	str = malloc(end - start + 1);
	if (!str)
		return (0);
	i = 0;
	while (start < end)
	{
		str[i] = s1[start];
		i++;
		start++;
	}
	str[i] = '\0';
	return (str);
} */
/* void	waiting_for_input(void);

void	syntax_error(char c)
{
	printf("syntax error near unexpected token `%c'\n", c);
	waiting_for_input();
} */

char	*ft_strstr(const char *big, const char *little)
{
	size_t	i;
	size_t	j;

	if (!(*little))
		return ((char *)big);
	i = 0;
	while (big[i])
	{
		j = 0;
		while (little[j] && big[i + j] && big[i + j] == little[j])
			j++;
		if (!(little[j]))
			return ((char *)&big[i]);
		i++;
	}
	return (0);
}

/* int	is_token_end(char c)
{
	if ((c >= '\t' && c <= '\r') || c == ' ')
		return (1);
	else if (c == '|')
		return (-1);
	return (0);
} */

/* char	*create_token(const char *str, size_t len)
{
	char			*token;
	char			*tmp;
	unsigned int	i;

	tmp = malloc((len + 1) * sizeof(char));
	if (tmp == 0)
		return (0);
	i = 0;
	while (i < len && str[i])
	{
		tmp[i] = str[i];
		i++;
	}
	tmp[i] = '\0';
	token = ft_strtrim(tmp, " \a\b\t\n\v\f\r");
	free(tmp);
	return (token);
} */

/* int	count_tokens_quotes(char *input)
{
	int		len;
	char	c;

	len = 0;
	while (*input && *input != '\'' && *input != '\"')
	{
		if (is_token_end(*input) <= 0 && len != 1)
			len = 1;
		input++;
	}
	if (!(*input))
		return (len);
	c = *input++;
	while (*input && *input != c)
		input++;
	if (*input && *(input + 1))
		len += count_tokens_quotes(++input);
	len++;
	return (len);
} */

/* int	quotes_end(char *input)
{
	int	end;

	end = 0;
	if (*input == '\'' || *input == '\"')
	{
		end++;
		while (input[end] && input[end] != *input)
			end++;
		end++;
	}
	else
	{
		while (input[end] && input[end] != '\'' && input[end] != '\"')
			end++;
	}
	return (end);
} */
/* 
char	**split_quotes(char *input)
{
	char	**tokens;
	char	**ptr;
	int		end;

	tokens = malloc((count_tokens_quotes(input) + 1) * sizeof(char *));
	if (!tokens)
		return (NULL);
	ptr = tokens;
	while (*input)
	{
		end = 0;
		end = quotes_end(input);
		if (end != 0)
		{
			*ptr = create_token(input, end);
			if (**ptr)
				ptr++;
			else
				free(*ptr);
		}
		input += end;
	}
	*ptr = NULL;
	return (tokens);
} */

int	count_strings(char **strs)
{
	int	i;

	i = 0;
	while (*strs)
	{
		i++;
		strs++;
	}
	return (i);
}

/* int	move_in_str(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	if (str[i] == c)
		i++;
	return (i);
}

int	count_char_tokens(char **input, char c)
{
	int		len;
	int		i;
	char	*tmp;

	len = 0;
	i = 0;
	while (input[i])
	{
		tmp = input[i++];
		if (*tmp == '\'' || *tmp == '\"')
			len++;
		else
		{
			while (*tmp)
			{
				tmp += move_in_str(tmp, c);
				len++;
			}
		}
	}
	return (len);
} */

/* int	count_inouts(char *str, char c)
{
	int	len;

	len = 0;
	while (*str)
	{
		str += move_in_str(str, c);
		if (*str == c && *(str + 1) == c)
			syntax_error(c);
		if (*(str - 1) == c)
			len++;
		if (*(str - 1) == c && *str == c)
			str++;	
	}
	return (len);
} */

/* int	count_inout_tokens(char **input)
{
	int		len;
	int		i;
	char	*tmp;

	len = 0;
	i = 0;
	while (input[i])
	{
		tmp = input[i++];
		if (*tmp == '\'' || *tmp == '\"')
			len++;
		else
			len += count_inouts(tmp, '<') + count_inouts(tmp, '>');
	}
	return (len);
} */

/* char	**split_inout(char **input)
{
	int		end;
	char	**tokens;
	char	**ptr;
	char	*str;

	tokens = malloc((count_inout_tokens(input) + 1) * sizeof(char *));
	if (!tokens)
		return (0);
	ptr = tokens;
	while (*input)
	{
		if (**input == '\'' || **input == '\"')
		{
			*ptr = *input;
			ptr++;
		}
		else
		{
			str = *input;
			while (*str)
			{
				end = 0;
				if ((*str == '<' && *(str + 1) == '<') || (*str == '>' && *(str + 1) == '>'))
					end = 2;
				else if (*str == '<' || *str == '>')
					end = 1;
				else
				{
					while (str[end] && str[end] != '<' && str[end] != '>')
						end++;
				}
				*ptr = create_token(str, end);
				if (**ptr)
					ptr++;
				else
					free(*ptr);
				str += end;
			}
		}
		input++;
	}
	*ptr = NULL;
	return (tokens);
} */

/* char	**split_char_tokens(char **input, char c)
{
	int		end;
	char	**tokens;
	char	**ptr;
	char	*str;

	tokens = malloc((count_char_tokens(input, c) + 1) * sizeof(char *));
	if (!tokens)
		return (0);
	ptr = tokens;
	while (*input)
	{
		if (**input == '\'' || **input == '\"')
		{
			*ptr = *input;
			ptr++;
		}
		else
		{
			str = *input;
			while (*str)
			{
				end = 0;
				if (*str == c)
					end = 1;
				else
				{
					while (str[end] && str[end] != c)
						end++;
				}
				*ptr = create_token(str, end);
				if (**ptr)
					ptr++;
				else
					free(*ptr);
				str += end;
			}
		}
		input++;
	}
	*ptr = NULL;
	return (tokens);
} */

/* void	print_tokens(char **tokens)
{
	while (*tokens)
	{
		printf("%s\n", *tokens);
		tokens++;
	}
} */

/* int	count_words_line(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if ((str[i] < '\a' || str[i] > '\r') && str[i] != ' ')
		{
			j++;
			while (str[i] && (str[i] < '\a' || str[i] > '\r') && str[i] != ' ')
				i++;
		}
		else
			i++;
	}
	return (j);
} */
/* 
int	count_words_total(char **input)
{
	int		len;
	int		i;
	char	*tmp;

	len = 0;
	i = 0;
	while (input[i])
	{
		tmp = input[i++];
		if (*tmp == '\'' || *tmp == '\"')
			len++;
		else
			len += count_words_line(tmp);
	}
	return (len);
} */

/* char	**split_spaces(char **input)
{
	int		end;
	char	**tokens;
	char	**ptr;
	char	*str;

	tokens = malloc((count_words_total(input) + 1) * sizeof(char *));
	if (!tokens)
		return (0);
	ptr = tokens;
	while (*input)
	{
		if (**input == '\'' || **input == '\"')
		{
			*ptr = *input;
			ptr++;
		}
		else
		{
			str = *input;
			while (*str)
			{
				end = 0;
				while (str[end] && ((str[end] > '\a' & str[end] < '\r') || str[end] == ' '))
					end++;
				while (str[end] && (str[end] < '\a' || str[end] > '\r') && str[end] != ' ')
					end++;
				*ptr = create_token(str, end);
				if (**ptr)
					ptr++;
				else
					free(*ptr);
				str += end;
			}
		}
		input++;
	}
	*ptr = NULL;
	return (tokens);
} */

/* char	**tokens_init(char *input)
{
	char	**tokens;
	char	**ptr;
	char	*tmp;
	char	**ptr2;
	char	**ptr3;

	tmp = ft_strtrim(input, " \a\b\t\n\v\f\r");
	free(input);
	input = tmp; //!! where is free tmp?
	ptr = split_quotes(input);
	ptr2 = split_spaces(ptr);
	ptr3 = split_inout(ptr2);
	tokens = split_char_tokens(ptr3, '|');
	//free(ptr);
	//ptr =
	return (tokens);
} */
/* 
void	waiting_for_input(void)
{
	char	*rl;
	char	*tmp;
	char	**tokens;

	while (1)
	{
		rl = readline("minishell > ");
		printf("rl: |%s|\n", rl);
		tmp = ft_strtrim(rl, " \a\b\t\n\v\f\r");
		printf("trimmed: |%s|\n", tmp);
		tokens = tokens_init(rl);
		print_tokens(tokens);
	}
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	waiting_for_input();
	return (0);
} */
