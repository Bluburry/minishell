#include "minishell.h"

int	count_tokens(char **input)
{
	int	i;

	i = 0;
	while (input[i])
		i++;
	return (i);
}

char	**expand_var_tokens(char **input, t_env *env, t_data *data)
{
	char	**tokens;
	char	**ptr;

	tokens = malloc((count_tokens(input) + 1) * sizeof(char *));
	if (!tokens)
		return (0);
	ptr = tokens;
	while (*input)
	{
		if (**input == '\'')
			*ptr = ft_strdup(*input);
		else
			*ptr = var_to_value(*input, env, data);
		ptr++;
		input++;
	}
	*ptr = NULL;
	return (tokens);
}
