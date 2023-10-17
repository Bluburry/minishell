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
	int		j;

	len = 0;
	i = 0;
	while (input[i])
	{
		j = 0;
		if (input[i][j] == '\'' || input[i][j] == '\"')
			len++;
		else
		{
			while (input[i][j])
			{
				j += move_in_str(input[i], c);
				len++;
			}
		}
		i++;
	}
	return (len);
}

int	scan_for_char(char **input, char c)
{
	int	i;
	int	j;

	i = 0;
	while (input[i])
	{
		j = 0;
		if (input[i][j] == '\'' || input[i][j] == '\"')
			i++;
		else
		{
			while (input[i][j])
			{
				if (input[i][j] == c)
					return (1);
				j++;
			}
		}
		i++;
	}
	return (0);
}

char	**split_char_tokens(char **input, char c)
{
	int		end;
	char	**tokens;
	int		i;
	int		j;
	int		t;

	if (scan_for_char(input, c) == 0)
		return (input);
	tokens = malloc((count_tokens(input, c) + 1) * sizeof(char *));
	if (!tokens)
		return (0);
	i = 0;
	t = 0;
	while (input[i])
	{
		j = 0;
		if (input[i][0] == '\'' || input[i][0] == '\"')
			tokens[t++] = input[i++];
		else
		{
			end = 0;
			while (input[i][j])
			{
				if (input[i][j] == c)
					end++;
				else
				{
					while (input[i][end] && input[i][end] != c)
						end++;
				}
				tokens[t] = create_token(input[i] + j, end);
				if (tokens[t][0])
					t++;
				else
					free(tokens[t]);
				j += end;
			}
		}
		i++;
	}
	tokens[t] = NULL;
	free(input);
	//free_ptrptr(input); //!algo de errado nao esta certo
	return (tokens);
}

void	print_tokens(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
		printf("%s\n", tokens[i++]);
}

char	**tokens_init(char *input)
{
	char	**tokens;
	char	**ptr;
	char	*tmp;

	tmp = ft_strtrim(input, " \a\b\t\n\v\f\r");
	free(input);
	input = tmp;
	ptr = split_quotes(input);
	tokens = split_char_tokens(ptr, '|');
	//tokens = split_char_tokens(tokens, '<'); //!algo de errado nao esta certo
	//tokens = split_char_tokens(tokens, '>'); //!algo de errado nao esta certo
	return (tokens);
}

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
		//free_ptrptr(tokens); //!algo de errado nao esta certo
	}
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	waiting_for_input();
	return (0);
}
