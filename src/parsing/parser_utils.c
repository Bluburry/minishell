#include "minishell.h"

void	dcp_cleaner(char **ptr)
{
	int	i;

	i = 0;
	if (!ptr)
		return ;
	while (ptr[i])
		free(ptr[i++]);
	free(ptr);
}

void	syntax_error(char c)
{
	printf("syntax error near unexpected token `%c'\n", c);
	waiting_for_input();
}
