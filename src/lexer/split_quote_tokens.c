#include "minishell.h"

int	count_tokens_quotes(char *input)
{
	int		len;
	char	c;

	len = 0;
	while (*input && *input != '\'' && *input != '\"')
	{
		if (len != 1)
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

char	check_if_valid(char **ptr)
{
	char	*str;
	char	c;

	if (!(*ptr))
		return ('\0');
	str = *ptr;
	if (*str == '\'' || *str == '\"')
	{
		if (*str != str[ft_strlen(str) - 1])
		{
			c = *str;
			return (c);
		}
	}
	return ('\0');
}

char	**split_quotes_tokens(char *input)
{
	char	**tokens;
	char	**ptr;
	int		end;
	char	c;

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
			c = check_if_valid(ptr);
			if (c != '\0')
{				syntax_error(2, c);
				dcp_cleaner(tokens);
				return (NULL);}
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
