#include "minishell.h"

void	ft_export(t_env *env, char **arglist)
{
	char	**vars;
	int		i;

	if (list_len(arglist) > 1)
		alter_env_var(env, arglist);
	else
	{
		vars = export_string(env);
		i = 0;
		while (i < env->size)
			printf("%s\n", vars[i++]);
		clear_chars(vars, env->size);
	}
}

void	ft_env(t_env *env, char **arglist)
{
	char	**vars;
	int		size;
	int		i;

	if (list_len(arglist) > 1)
		printf("minishell: env: too many arguments\n");
	vars = env_string(env);
	i = 0;
	size = env->size - num_invalid_env_vars(env);
	while (i < size)
		printf("%s\n", vars[i++]);
	clear_chars(vars, size);
}

void	ft_pwd(void)
{
	char	*str;

	str = pwd();
	printf("%s\n", str);
	free(str);
}

void	ft_test()
{
	while (1)
		continue ;
}

static void	execute(t_tok tk, t_data *d, uint32_t i)
{
	if (ft_strncmp(tk.path, "echo", 5) == 0)
		ft_echo(tk.arglist);
	else if (ft_strncmp(tk.path, "pwd", 4) == 0)
		ft_pwd();
	else if (ft_strncmp(tk.path, "env", 4) == 0)
		ft_env(d->env, tk.arglist);
	else if (ft_strncmp(tk.path, "unset", 6) == 0)
		unset_env_var(d->env, tk.arglist);
	else if (ft_strncmp(tk.path, "export", 8) == 0)
		ft_export(d->env, tk.arglist);
	else if (ft_strncmp(tk.path, "exit", 5) == 0)
		ft_exit(d, tk.arglist);
	else if (ft_strncmp(tk.path, "cd", 3) == 0)
			cd(d->env, tk.arglist[1]);
	else
		d->ret_status = run_exe(tk.path, tk.arglist, d->env,
				i == d->cmds->size - 1);
}

bool	exec_comm_list(t_data *data)
{
	int		i;

	if (data->cmds == NULL)
		return (false);
	i = -1;
	while (++i < (int)data->cmds->size)
	{
		if (data->cmds->tks[i].type == none)
			return (false);
		else if (data->cmds->tks[i].type == exec)
			execute(data->cmds->tks[i], data, i);
		else if (data->cmds->tks[i].type == r_pipe)
			exec_pipe(data);
		else if (data->cmds->tks[i].type == r_out)
			redir_trunc(data->cmds->tks[i].path);
		else if (data->cmds->tks[i].type == r_in)
			redir_in(data->cmds->tks[i].path);
		else if (data->cmds->tks[i].type == r_append)
			redir_appd(data->cmds->tks[i].path);
		else if (data->cmds->tks[i].type == r_heredoc)
			redir_heredoc(data->cmds->tks[i].path);
	}
	return (true);
}
