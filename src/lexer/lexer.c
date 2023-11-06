#include "minishell.h"

char	**lexer(char *input, t_env *env, t_data *data)
{
	char	**tokens;
	int		i;

	i = -1;
	if (!input || !(*input))
		return (NULL);
	tokens = tokens_init(input, env);
	// printf("\n\ntokens:\n\n");
	// while (tokens[++i])
	// 	printf("%s\n", tokens[i]);
	data->strlist = tokens;
	return (tokens);
}
