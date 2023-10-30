#include "minishell.h"
#include <signal.h>

struct sigaction	sa;

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
	t_env	*env;

	(void)argc;
	(void)argv;
	ft_bzero(&sa, sizeof(sa));
	sa.sa_sigaction = sig_handler;
	sa.sa_flags = SA_SIGINFO;
	//sigaddset(&sa.sa_mask, SIGQUIT);
	//sigemptyset(&sa.sa_mask);
	sigaction(SIGQUIT, &sa, NULL);
	//sigaction(SIGUSR2, &sa, NULL);
	env = create_env_struct(envp);
	/* add_new_env_var(env, "TEST=24");
	add_new_env_var(env, "TEST2");
	add_new_env_var(env, "TEST3=");
	unset_env_var(env, "TEST");
	int i = -1;
	while (++i < env->size)
	{
		printf("%s\n", env->vars[i]);
	}
	printf("\n\nSearch LANG: %s\n", get_env_var(env, "LANG"));
	printf("\n\nSearch PWD: %s\n", get_env_var(env, "PWD"));
	printf("\n\nSearch LS_COLORS: %s\n", get_env_var(env, "LS_COLORS"));
	printf("\n\nSearch LSCOLORS: %s\n", get_env_var(env, "LSCOLORS"));
	printf("\n\nSearch MAKEFLAGS: %s\n", get_env_var(env, "MAKEFLAGS"));
	printf("\n\nSearch SHLVL: %s\n", get_env_var(env, "SHLVL"));
	printf("\n\nSearch TEST: %s\n", get_env_var(env, "TEST"));
	add_new_env_var(env, "TEST=42");
	printf("\n\nSearch TEST: %s\n", get_env_var(env, "TEST"));
	printf("\n\nSearch TEST2: %s\n", get_env_var(env, "TEST2"));
	printf("\n\nSearch TEST3: %s\n", get_env_var(env, "TEST3"));
	add_new_env_var(env, "TEST4=169");
	char **test = env_string(env);
	printf("\n\ntest env_string:\n");
	i = -1;
	int n = num_invalid_env_vars(env);
	while (++i < env->size - n)
	{
		printf("%s\n", test[i]);
	}
	clear_chars(test, env->size - n); 
	printf("\n\ntest export_string:\n");
	test = export_string(env);
	i = -1;
	while (++i < env->size)
	{
		printf("%s\n", test[i]);
	}
	clear_chars(test, env->size); */
	waiting_for_input(env);
	clear_env_struct(env);
	rl_clear_history();
	return (0);
}
