#include "minishell.h"


void	find_exe(t_tok token, t_data *data)
{
	char	*path;

	path = find_exe_path(data->env, token.path);
	if (path)
		run_exe(path, token.arglist);
	else
		printf("%s: command not found\n", token.arglist[0]);
}

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
