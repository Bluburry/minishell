#include "minishell.h"

int	is_operator(char c, char *operators)
{
	while (*operators)
		if (c == *operators++)
			return (1);
	return (0);
}

int	count_merge_tokens(char **input)
{
	int		len;
	int		i;
	int		flag;
	char	*tmp;

	flag = 0;
	len = 0;
	i = -1;
	while (input[++i])
	{
		tmp = input[i];
		if ((is_space(*tmp)) || is_operator(*tmp, "<>|"))
		{
			len++;
			flag = 0;
		}
		else if (flag == 0)
		{
			len++;
			flag = 1;
		}
	}
	return (len);
}

/* char	*join_tokens(char *token1, char *token2)
{
	char	*str;
	char	c;
	int		i;

	str = malloc(ft_strlen(token1) + ft_strlen(token2) + 1);
	if (!str)
		return (0);
	if (*token1 == '\'' || *token1 == '\"')
		c = *token1++;
	i = 0;
	while (*token1 && *token1 != c)
		str[i++] = *token1++;
	if (*token2 == '\'' || *token2 == '\"')
		c = *token1++;
	else
		c = '\0';
	while (*token2 && *token2 != c)
		str[i++] = *token2++;
	str[i] = '\0';
	return (str);
} */

char	**merge_tokens_cleanup(char **input)
{
	char	**tokens;
	char	**ptr;

	tokens = malloc((count_merge_tokens(input) + 1) * sizeof(char *));
	if (!tokens)
		return (0);
	ptr = tokens;
	while (*input)
	{
		if (is_space(**input))
			input++;
		if (is_operator(**input, "<>|") || !(*(input + 1)) || (*(input + 1)
				&& (is_space(**(input + 1))
					|| is_operator(**(input + 1), "<>|\0"))))
			*ptr = ft_strdup(*input);
		else
		{
			*ptr = ft_strjoin(*input, *(input + 1));
			input++;
		}
		ptr++;
		input++;
	}
	*ptr = NULL;
	return (tokens);
}
