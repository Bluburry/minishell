#include "libft.h"
#include "minishell.h"
#include "structures.h"
#include <curses.h>

void	ft_export(t_env *env)
{
	char	**vars;
	int		i;

	vars = export_string(env);
	i = 0;
	while (i < env->size)
		printf("%s\n", vars[i++]);
	clear_chars(vars, env->size);
}

void	ft_env(t_env *env)
{	
	char	**vars;
	int		size;
	int		i;

	vars = env_string(env);
	i = 0;
	size = env->size - num_invalid_env_vars(env);
	while (i < size)
		printf("%s\n", vars[i++]);
	clear_chars(vars, size);
}

static void	execute(t_tok token, t_data *data)
{
	if (ft_strncmp(token.path, "echo", 5))
		ft_echo(token.arglist);
	else if (ft_strncmp(token.path, "cd", 3))
	{
		if (list_len(token.arglist) > 2)
			printf("minishell: cd: too many arguments\n");
		else
			cd(data->env, token.arglist[1]);
	}
	else if (ft_strncmp(token.path, "pwd", 4))
		pwd();
	else if (ft_strncmp(token.path, "env", 4))  // ! arguments?
		ft_env(data->env);
	/* else if (ft_strncmp(token.path, "exit", 5))
		ft_exit(data) */
	else if (ft_strncmp(token.path, "unset", 6)) // ! how does unset behave in bash??
		unset_env_var(data->env, token.arglist[1]);
	else if (ft_strncmp(token.path, "export", 8)) // ! how does export behave in bash??
		ft_export(data->env);
/* 	else
	 exec; */
}

bool	exec_comm_list(t_data *data)
{
	if (data->cmds == NULL)
		return (false);
/* 	if (data->cmds->tks[0].type == exit_b)
		data->is_exiting = true; */
	if (data->cmds->tks[0].type == none)
		return (false);
	if (data->cmds->tks[0].type == exec)
		execute(data->cmds->tks[0], data);
	return (true);
}
/* if (data->cdms.tks[0] == exec)
	test_exec(data->cdms.tks[0]);



if fr_strncmp(tk->path, "exit") == 0
	ft_exit()
	else if fr_strncmp(tk->path, "echo") == 0
	else
	exec_executable () */