#include "minishell.h"

int	run_exe(char *path, char **args, t_env *env)
{
	int	pid;

	pid = fork();
	if (!pid)
	{
		if (execve(path, args, env->vars) == -1)
			return (perror("executable error"), 0);
		return (1);
	}
	if (waitpid(pid, NULL, 0) == 0)
		return (0);
	return (1);
}