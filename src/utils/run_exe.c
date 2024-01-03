#include "minishell.h"

int	run_exe(char *path, char **args, t_env *env, bool is_last)
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
	if (is_last)
		waitpid(pid, &status, 0);
	set_signals_base();
	return (WEXITSTATUS(status));
}
