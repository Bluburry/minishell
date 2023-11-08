#include "minishell.h"

char	**lexer(char *input, t_env *env)
{
	char	**tokens;
	int		i;

	i = -1;
	if (!input || !(*input))
		return (NULL);
	tokens = tokens_init(input, env);
	printf("\n\ntokens:\n\n");
	if (tokens)
		while (tokens[++i])
			printf("%s\n", tokens[i]);
	return (tokens);
}
