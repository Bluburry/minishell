#include "minishell.h"

void	parser(char *input)
{
	char	**tokens;

	if (!input || !(*input))
		return ;
	tokens = tokens_init(input);
	dcp_cleaner(tokens);
	//!!! call funtion that executes instructions HERE
}
