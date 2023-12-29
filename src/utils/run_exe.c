#include "minishell.h"

void	find_exe(t_tok token, t_data *data)
{
	char	*path;

	path = find_exe_path(data->env, token.path);
	if (path)
		run_exe(path, token.arglist, data->env, false); // needs to be changed
	else
		printf("%s: command not found\n", token.arglist[0]);
}

int	run_exe(char *path, char **args, t_env *env, bool is_last)
{
	pid_t	pid;
	int		status;

	if (!path || !*path)
		return (0);
	status = 0;
	pid = fork();
	if (!pid)
	{
		set_signals_fork();
		execve(path, args, env->vars);
	}
	set_signals_base();
	if (is_last)
		waitpid(pid, &status, 0);
	return (!WEXITSTATUS(status));
}
