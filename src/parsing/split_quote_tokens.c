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

char	**split_quotes_tokens(char *input)
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
}
