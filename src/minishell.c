#include "../include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	//char	*rl;
	t_env	*env;

	(void)argc;
	(void)argv;
	env = create_env_struct(envp);
	int i = -1;
	while (++i < env->size)
	{
		printf("%s\n", env->vars[i]);
	}
	while (1)
	{
		rl = readline("minishell > ");
		printf("rl: %s\n", rl);
	}
	clear_env_struct(env);
	return (0);
}