#include "minishell.h"

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

int	check_if_valid(char **ptr, char **tokens)
{
	char	*str;
	char	c;

	str = *ptr;
	if (*str == '\'' || *str == '\"')
	{
		if (*str != str[ft_strlen(str) - 1])
		{
			c = *str;
			free(*ptr);
			*ptr = NULL;
			dcp_cleaner(tokens);
			return (1);
		}
	}
	return (0);
}

char	**split_quotes_tokens(char *input, int *flag)
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
			*flag = check_if_valid(ptr, tokens);
			if (*flag)
				return (NULL);
			ptr++;
		}
		input += end;
	}
	*ptr = NULL;
	return (tokens);
}

/* 			if (**ptr)
				ptr++;
			else
				free(*ptr); */

/* potato	wooo! aie< "dasdadad342"           4234 	oo */


