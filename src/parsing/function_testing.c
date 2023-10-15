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
	unsigned int	i;

	token = malloc((len + 1) * sizeof(char));
	if (token == 0)
		return (0);
	i = 0;
	while (i < len && *str)
	{
		token[i] = str[i];
		i++;
	}
	token[i] = '\0';
	return (token);
}

/* int	count_tokens_quotes(char *input)
{
	int		len;
	int		flag;
	char	c;

	len = 0;
	while (*input && *input != '\'' && *input != '\"')
	{
		if (is_token_end(*input) <= 0 && len != 1)
			len = 1;
		input++;
	}
	if (!(*input))
		return (0);
	c = *input++;
	flag = -1;
	while (*input)
	{
		while (*input && *input != c)
			input++;
		if (*input)
		{
			flag = -flag;
			input++;
		}
		len++;
	}
	printf("flag: %d\n", flag);
	return (len);
} */

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
			ptr++;
		}
		input += end;
	}
	*ptr = NULL;
	return (q_tokens);
}

void	print_tokens(char **tokens)
{
	while (*tokens)
	{
		printf("%s\n", *tokens);
		tokens++;
	}
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
		tokens = split_quotes(rl);
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
}
