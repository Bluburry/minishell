#include "minishell.h"

int	run_exe(char *path, char **args)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (!pid)
		execve(path, args, NULL);
	waitpid(pid, &status, 0);
	return (!WEXITSTATUS(status));
}
