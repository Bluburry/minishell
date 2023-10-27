#include "minishell.h"

void	waiting_for_input(t_env *env)
{
	char	*rl;

	while (1)
	{
		rl = readline("minishell > ");
		printf("rl: %s\n", rl);
		lexer(rl, env);
		add_history(rl);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_env		*env;

	(void)argc;
	(void)argv;
	env = create_env_struct(envp);
	waiting_for_input(env);
	clear_env_struct(env);
	rl_clear_history();
	return (0);
}
