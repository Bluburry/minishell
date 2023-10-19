#include "minishell.h"

void	waiting_for_input()
{
	char	*rl;

	while (1)
	{
		rl = readline("minishell > ");
		printf("rl: %s\n", rl);
		if (ft_strncmp(rl, "exit", 4))
			break ;
		parser(rl);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;

	(void)argc;
	(void)argv;
	env = create_env_struct(envp);
	add_new_env_var(env, "TEST=24");
	int i = -1;
	while (++i < env->size)
	{
		printf("%s\n", env->vars[i]);
	}
	printf("\n\nSearch: %s\n", get_env_var(env, "LANG"));
	printf("\n\nSearch: %s\n", get_env_var(env, "PWD"));
	printf("\n\nSearch: %s\n", get_env_var(env, "LS_COLORS"));
	printf("\n\nSearch: %s\n", get_env_var(env, "TEST"));
	add_new_env_var(env, "TEST=42");
	printf("\n\nSearch: %s\n", get_env_var(env, "TEST"));
	unset_env_var(env, "TEST");
	char **test = env_string(env);
	printf("\n\ntest env_string:\n");
	i = -1;
	while (++i < env->size)
	{
		printf("%s\n", test[i]);
	}
	clear_chars(test, env->size);
	printf("\n\ntest export_string:\n");
	test = export_string(env);
	i = -1;
	while (++i < env->size)
	{
		printf("%s\n", test[i]);
	}
	clear_chars(test, env->size);

	//waiting_for_input();
	clear_env_struct(env);
	return (0);
}
