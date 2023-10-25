#include "minishell.h"

void	waiting_for_input()
{
	char	*rl;

	while (1)
	{
		rl = readline("minishell > ");
		printf("rl: %s\n", rl);
		parser(rl);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;

	(void)argc;
	(void)argv;
	env = create_env_struct(envp);

//	int	i = -1;
//	while (++i < env->size)
//	{
//		printf("%s\n", env->vars[i]);
//	}
	//printf("\n\nSearch: %s\n", get_env_var(env, "LANG"));
	//printf("\n\nSearch: %s\n", get_env_var(env, "PWD"));
	//printf("\n\nSearch: %s\n", get_env_var(env, "LS_COLORS"));
	//var_to_value("$s");
	//var_to_value("$USERNAME $DISPLAY", env);
	//var_to_value("$USERNAME", env);
	ft_printf("\n%s\n\n", var_to_value("is this working yet? $USERNAME test $DISPLAY are you doctor?", env));
	waiting_for_input();
	clear_env_struct(env);
	return (0);
}
