#include "minishell.h"

int	run_exe(char *path, char **args, t_env *env)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (!pid)
		execve(path, args, env->vars);
	waitpid(pid, &status, 0);
	return (!WEXITSTATUS(status));
}
