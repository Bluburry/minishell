#include "minishell.h"

void	waiting_for_input(t_env *env)
{
	char	*rl;

	while (1)
	{
		rl = readline("minishell > ");
		printf("rl: %s\n", rl);
		lexer(rl, env);
	}
}

int	main(int argc, char **argv, char **envp)
{
//	t_env	*env;

	(void)argc;
	(void)argv;
	(void)envp;
/* 	env = create_env_struct(envp);
	int i = -1;
	while (++i < env->size)
	{
		printf("%s\n", env->vars[i]);
	} */
/* 	printf("\n\nSearch: %s\n", get_env_var(env, "LANG"));
	printf("\n\nSearch: %s\n", get_env_var(env, "PWD"));
	printf("\n\nSearch: %s\n", get_env_var(env, "LS_COLORS")); */
	waiting_for_input(env);
	//clear_env_struct(env);
	return (0);
}
