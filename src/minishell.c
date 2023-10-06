#include "minishell.h"

int	main(void)
{
	char	*rl;

	while (1)
	{
		rl = readline("minishell > ");
		printf("rl: %s\n", rl);
	}
	return (0);
}