#include "libft.h"
#include "minishell.h"
#include "structures.h"
#include <curses.h>

void	too_many_args(char * str)
{
	printf("minishell: %s: too many arguments\n", str);
}

void	ft_export(t_env *env, char **arglist)
{
	char	**vars;
	int		i;

	if (list_len(arglist) > 1)
		add_new_env_var(env, arglist); // TIAGO -> alterar esta func para receber char**
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
		too_many_args("env");
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

static void	execute(t_tok token, t_data *data)
{
	if (ft_strncmp(token.path, "echo", 5))
		ft_echo(token.arglist);
	else if (ft_strncmp(token.path, "pwd", 4))
		ft_pwd();
	else if (ft_strncmp(token.path, "env", 4))
		ft_env(data->env, token.arglist);
	else if (ft_strncmp(token.path, "unset", 6))
		unset_env_var(data->env, token.arglist); // TIAGO -> alterar esta func para receber char**
	else if (ft_strncmp(token.path, "export", 8))
		ft_export(data->env, token.arglist);
	else if (ft_strncmp(token.path, "cd", 3) || ft_strncmp(token.path, "exit", 5)) // adicionar exit aqui
	{
		if (list_len(token.arglist) > 2)
			too_many_args(token.arglist[0]);
		else if (ft_strncmp(token.path, "cd", 3))
			cd(data->env, token.arglist[1]);
/* 		else
		 ft_exit(token.arglist); */
	}
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
