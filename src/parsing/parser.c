#include "minishell.h"

void	parser(char *input)
{
	char	**tokens;
	int		i;

	i = -1;
	if (!input || !(*input))
		return ;
	tokens = tokens_init(input);
	while (tokens[++i])
		printf("^%s^\n", tokens[i]);
	dcp_cleaner(tokens);
	//!!! call funtion that executes instructions HERE
}
