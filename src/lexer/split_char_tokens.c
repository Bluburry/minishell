#include "minishell.h"

int	find_char(char *str, char c)
{
	int	i;
	int	counter;

	i = -1;
	counter = 0;
	while (str[++i])
		if (str[i] == c)
			counter++;
	return (counter);
}

char	*sdf(char *tmp, char c, int *len)
{
	while (*tmp && *tmp != c)
		tmp++;
	if (*(tmp - 1) != c)
		(*len)++;
	if (*tmp)
		tmp++;
	return (tmp);
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
		if (*tmp == '\'' || *tmp == '\"')
			len++;
		else
		{
			len += find_char(tmp, c);
			if (*tmp == c)
				tmp++;
			while (*tmp)
				tmp = sdf(tmp, c, &len);
		}
	}
	return (len);
}

char	**tokenize_char(char *input, char **ptr, char c)
{
	char	*str;
	int		end;

	str = input;
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
	return (ptr);
}

char	**split_char_tokens(char **input, char c)
{
	char	**tokens;
	char	**ptr;
	int		flag;

	tokens = malloc((count_char_tokens(input, c) + 1) * sizeof(char *));
	if (!tokens)
		return (0);
	ptr = tokens;
	while (*input)
	{
		flag = 0;
		ptr = check_for_quotes(*input, ptr, &flag);
		if (flag == 0)
			ptr = tokenize_char(*input, ptr, c);
		input++;
	}
	*ptr = NULL;
	ptr = space_tokens_cleanup(tokens);
	dcp_cleaner(tokens);
	return (ptr);
}
