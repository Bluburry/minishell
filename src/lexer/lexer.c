#include "minishell.h"

void	lexer(char *input, t_env *env)
{
	char	**tokens;
	int		i;

	i = -1;
	if (!input || !(*input))
		return ;
	tokens = tokens_init(input, env);
	printf("\n\ntokens:\n\n");
	while (tokens[++i])
		printf("%s\n", tokens[i]);
	dcp_cleaner(tokens);
	//!!! return tokens here
}
