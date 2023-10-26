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

typedef struct s_input
{
	int	s_quote;
	int	d_quote;
	int	s_red_in;
	int	s_red_out;
	int	d_red_in;
	int	d_red_out;
	int	dollar;
	int	pipe;
}	t_input;

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

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		if (s1[i] != s2[i])
			return (((unsigned char)s1[i] - (unsigned char)s2[i]));
		i++;
	}
	return (0);
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
}

int	is_token_end(char c)
{
	if ((c >= '\t' && c <= '\r') || c == ' ')
		return (1);
	else if (c == '|')
		return (-1);
	return (0);
}

char	*create_token(const char *str, size_t len)
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
}

int	count_tokens_quotes(char *input)
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
}

int	quotes_end(char *input)
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
}

char	**split_quotes(char *input)
{
	char	**q_tokens;
	char	**ptr;
	int		end;

	q_tokens = malloc((count_tokens_quotes(input) + 1) * sizeof(char *));
	if (!q_tokens)
		return (NULL);
	ptr = q_tokens;
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
	return (q_tokens);
}
 
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

int	move_in_str(char *str, char c)
{
	int	i;

	i = 0;
	if (str[i] == c)
		i++;
	else
	{
		while (str[i] && str[i] != c)
			i++;
	}
	return (i);
}

int	count_tokens(char **input, char c)
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
}

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(s) + 1;
	while (i < len)
	{
		if (s[i] == (char)c)
			return ((char *) &s[i]);
		i++;
	}
	return (0);
}

//! NEW FUNCTION
// CHECKS IF THE SPLITTER C EXISTS IN THE STRING ARRAY
int	check_for_splitter(char **input, char c)
{
	while (*input)
	{
		if (ft_strchr(*input, c))
			return (1);
		input++;
	}
	return (0);
}

char	**split_tokens(char **input, char c)
{
	int		end;
	char	**tokens;
	char	**ptr;
	char	*str;

	if (!check_for_splitter(input, c))
		return NULL;
	tokens = malloc((count_tokens(input, c) + 1) * sizeof(char *));
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
}

void	print_tokens(char **tokens)
{
	while (*tokens)
	{
		printf("%s\n", *tokens);
		tokens++;
	}
}

void	clear_chars(char **str, int size)
{
	int	i;

	i = -1;
	while (++i < size)
	{
		free(str[i]);
	}
	free(str);
}

char	**tokens_init(char *input)
{
	char	**tokens;
	char	**ptr;
	char	*tmp;

	tmp = ft_strtrim(input, " \a\b\t\n\v\f\r");
	//free(input);
	ptr = split_quotes(tmp);
	free(tmp);
	tokens = split_tokens(ptr, '|');
	if (tokens)
		clear_chars(ptr, count_strings(ptr));
	else
		tokens = ptr;
	ptr = split_tokens(tokens, '<');
	if (ptr)
		clear_chars(tokens, count_strings(tokens));
	else
		ptr = tokens;
	//free(tokens);
	return (ptr);
}

void	waiting_for_input(void)
{
	char	*rl = "asd ! ad| ecj \"asd\" < asda";
	char	*tmp;
	char	**tokens;

	//printf("rl: |%s|\n", rl);
	tmp = ft_strtrim(rl, " \a\b\t\n\v\f\r");
	printf("trimmed: |%s|\n", tmp);
	free(tmp);
	tokens = tokens_init(rl);
	print_tokens(tokens);
	clear_chars(tokens, count_strings(tokens));

	/* while (1)
	{
		rl = readline("minishell > ");
		if (!ft_strncmp(rl, "exit", ft_strlen("exit")))
			break ;
		printf("rl: |%s|\n", rl);
		tmp = ft_strtrim(rl, " \a\b\t\n\v\f\r");
		printf("trimmed: |%s|\n", tmp);
		free(tmp);
		tokens = tokens_init(rl);
		print_tokens(tokens);
		//clear_chars(tokens, count_strings(tokens));
	} */
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	waiting_for_input();
	return (0);
}
