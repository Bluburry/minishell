#include "minishell.h"

int	count_tokens(char **input)
{
	int	i;

	i = 0;
	while (input[i])
		i++;
	return (i);
}

char	**expand_var_tokens(char **input)
{
	char	**tokens;
	char	**ptr;
	int		flag;

	tokens = malloc((count_tokens(input) + 1) * sizeof(char *));
	if (!tokens)
		return (0);
	ptr = tokens;
	while (*input)
	{
		flag = 0;
		if (**input == '\'')
			*ptr = ft_strdup(*input);
		else 
			*ptr = var_to_value(*input);
		ptr++
		input++;
	}
	*ptr = NULL;
	return (tokens);
}
