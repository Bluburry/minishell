#include "minishell.h"

int	move_in_str(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	if (str[i] == c)
		i++;
	return (i);
}

int	find_char(char *str, char c)
{
	int	i;
	int	counter;

	i = -1;
	counter = 0;
	while(str[++i])
		if (str[i] == c)
			counter++;
	return (counter);
}

int	count_char_tokens(char **input, char c)
{
	int		len;
	int		i;
	char	*tmp;

	len = 0;
	i = -1;
	while (input[++i])
	{
		tmp = input[i];
		if (tmp[0] == '\'' || tmp[0] == '\"')
			len++;
		else
		{
			len += find_char(tmp, c);
			if (*tmp == c)
				tmp++;
			while (*tmp)
			{
				while (*tmp && *tmp != c)
					tmp++;
				if (*(tmp - 1) != c)
					len++;
				if (*tmp)
					tmp++;
			}
		}
	}
	return (len);
}

char	**split_char_tokens(char **input, char c)
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
			*ptr = ft_strdup(*input);
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