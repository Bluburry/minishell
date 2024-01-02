#include "minishell.h"

char	**lexer(char *input, t_env *env, t_data *data)
{
	char	**tokens;

	if (!input || !(*input))
		return (NULL);
	tokens = tokens_init(input, env);
	data->strlist = tokens;
	return (tokens);
}
