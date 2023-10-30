#include "minishell.h"

int	count_words_line(char *str)
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
			while (str[i] && (str[i] < '\a' || str[i] > '\r')
				&& str[i] != ' ')
				i++;
		}
		else
			i++;
	}
	return (j);
}

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
}

char	**idk(char *input, char **ptr)
{
	char	*str;
	int		end;

	str = input;
	while (*str)
	{
		end = 0;
		while (str[end] && ((str[end] > '\a' && str[end] < '\r')
				|| str[end] == ' '))
			end++;
		while (str[end] && (str[end] < '\a' || str[end] > '\r')
			&& str[end] != ' ')
			end++;
		*ptr = create_token(str, end);
		if (**ptr)
			ptr++;
		else
			free(*ptr);
		str += end;
	}
	return (ptr);
}

char	**split_space_tokens(char **input)
{
	char	**tokens;
	char	**ptr;
	int		flag;

	tokens = malloc((count_words_total(input) + 1) * sizeof(char *));
	if (!tokens)
		return (0);
	ptr = tokens;
	while (*input)
	{
		flag = 0;
		ptr = check_for_quotes(*input, ptr, &flag);
		if (flag == 0)
			ptr = idk(*input, ptr);
		input++;
	}
	*ptr = NULL;
	return (tokens);
}
