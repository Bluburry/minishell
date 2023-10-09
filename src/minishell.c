#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*rl;
	t_envi	*env;

	(void)argc;
	(void)argv;
	env = get_env_var(envp);
	while (env != NULL)
	{
		printf("%s=%s\n", env->var, env->val);
		env->next;
	}
	while (1)
	{
		rl = readline("minishell > ");
		printf("rl: %s\n", rl);
	}
	return (0);
}