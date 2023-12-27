#include "minishell.h"
#include <bits/types/siginfo_t.h>

void	find_exe(t_tok token, t_data *data)
{
	char	*path;

	path = find_exe_path(data->env, token.path);
	if (path)
		run_exe(path, token.arglist, data->env);
	else
		printf("%s: command not found\n", token.arglist[0]);
}


int	run_exe(char *path, char **args, t_env *env)
{
	pid_t	pid;
	int		status;

	if (!path || !*path)
		return (0);
	pid = fork();
	set_signals_fork();
	if (!pid)
	{
		execve(path, args, env->vars);
	}
	waitpid(pid, &status, 0);
	set_signals_base();
	return (!WEXITSTATUS(status));
}
