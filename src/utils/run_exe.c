#include "minishell.h"

int	run_exe(char *path, char **args, t_env *env)
{
	pid_t	pid;
	int		status;

	if (!path || !*path)
		return (0);
	status = 0;
	pid = fork();
	set_signals_fork();
	if (!pid)
	{
		execve(path, args, env->vars);
	}
	set_signals_base();
	return (WEXITSTATUS(status));
}
