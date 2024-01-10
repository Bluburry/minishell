/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_comms.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: remarque <remarque@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 14:40:48 by remarque          #+#    #+#             */
/*   Updated: 2024/01/10 14:40:49 by remarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_export(t_env *env, char **arglist)
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
	return (1);
}

int	ft_env(t_env *env, char **arglist)
{
	char	**vars;
	int		size;
	int		i;

	if (list_len(arglist) > 1)
	{
		printf("minishell: env: too many arguments\n");
		return (1);
	}
	vars = env_string(env);
	i = 0;
	size = env->size - num_invalid_env_vars(env);
	while (i < size)
		printf("%s\n", vars[i++]);
	clear_chars(vars, size);
	return (0);
}

int	ft_pwd(void)
{
	char	*str;

	str = pwd();
	printf("%s\n", str);
	free(str);
	return (0);
}

static void	execute(t_tok tk, t_data *d)
{
	if (ft_strncmp(tk.path, "echo", 5) == 0)
		d->ret_status = ft_echo(tk.arglist);
	else if (ft_strncmp(tk.path, "pwd", 4) == 0)
		d->ret_status = ft_pwd();
	else if (ft_strncmp(tk.path, "env", 4) == 0)
		d->ret_status = ft_env(d->env, tk.arglist);
	else if (ft_strncmp(tk.path, "unset", 6) == 0)
		d->ret_status = unset_env_var(d->env, tk.arglist);
	else if (ft_strncmp(tk.path, "export", 8) == 0)
		d->ret_status = ft_export(d->env, tk.arglist);
	else if (ft_strncmp(tk.path, "exit", 5) == 0)
		d->ret_status = ft_exit(d, tk.arglist);
	else if (ft_strncmp(tk.path, "cd", 3) == 0)
		d->ret_status = cd(d->env, tk.arglist);
	else
	{
		run_exe(tk.path, tk.arglist, d->env);
		d->has_executed = true;
	}
}

bool	exec_comm_list(t_data *data)
{
	auto int i = -1, status = 0;
	if (data->cmds == NULL)
		return (false);
	while (++i < (int)data->cmds->size)
	{
		if (data->cmds->tks[i].type == exec)
			execute(data->cmds->tks[i], data);
		else if (data->cmds->tks[i].type == r_pipe)
			exec_pipe(data);
		else if (data->cmds->tks[i].type == r_out)
			redir_trunc(data->cmds->tks[i].path);
		else if (data->cmds->tks[i].type == r_in)
			redir_in(data->cmds->tks[i].path);
		else if (data->cmds->tks[i].type == r_append)
			redir_appd(data->cmds->tks[i].path);
		else if (data->cmds->tks[i].type == r_heredoc)
			if (redir_heredoc(data->cmds->tks[i].path, data) == 130)
				break ;
	}
	while (wait(&status) > 0)
		continue ;
	if (data->has_executed == true)
		data->ret_status = WEXITSTATUS(status);
	return (true);
}
