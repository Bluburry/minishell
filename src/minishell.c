#include "../include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*rl;

	(void)argc;
	(void)argv;
	while (*envp)
	{
		printf("%s\n", *envp);
		envp++;
	}
	while (1)
	{
		rl = readline("minishell > ");
		printf("rl: %s\n", rl);
	}
	return (0);
}