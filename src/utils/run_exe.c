#include "minishell.h"

int	run_exe(char *path, char **args, t_env *env)
{
	pid_t	pid;

	if (!path || !*path)
		return (0);
	pid = fork();
	set_signals_fork();
	if (!pid)
	{
		execve(path, args, env->vars);
	}
	set_signals_base();
	return (true);
}
