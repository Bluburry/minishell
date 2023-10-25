#include "minishell.h"

int	count_space_tokens(char **input)
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
		if (!(is_space(*tmp)))
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

char	**space_tokens_cleanup(char **input)
{
	char	**tokens;
	char	**ptr;
	int		flag;

	tokens = malloc((count_space_tokens(input) + 1) * sizeof(char *));
	if (!tokens)
		return (0);
	ptr = tokens;
	flag = 0;
	while (*input)
	{
		if (!(is_space(**input)) || flag == 0)
		{
			*ptr = ft_strdup(*input);
			ptr++;
		}
		if ((is_space(**input)))
			flag = 1;
		else
			flag = 0;
		input++;
	}
	*ptr = NULL;
	return (tokens);
}
