#include "minishell.h"

/* static void	print_strlist(char **list)
{
	uint32_t	i;

	i = 0;
	while (list[i])
	{
		if (list[i][0] == 31)
			printf("NEXT HAD QUOTES\n");
		printf("%s\n", list[i++]);
	}
} */

/* static void	print_cmda(t_cmda *cmds)
{
	const char	*strs[7] = {"NONE", "EXEC", "PIPE", "OUT",
		"IN", "APPEND", "HEREDOC"};

	if (!cmds->tks)
		return ;
	for (uint32_t i = 0; i < cmds->size; i++)
	{
		printf("%d %s : \"%s\"",cmds->tks[i].type,
			strs[cmds->tks[i].type], cmds->tks[i].path);
		if (cmds->tks[i].arglist) {
			printf(" :");
			for (uint32_t j = 0; cmds->tks[i].arglist[j]; j++)
				printf(" \"%s\"", cmds->tks[i].arglist[j]);
		}
		printf("\n");
	}
} */

static void	reset_singleton(t_data *d)
{
	if (d->fd_in != -1)
		close(d->fd_in);
	d->fd_in = -1;
	dup2(d->stdin, 0);
	dup2(d->stdout, 1);
	d->pipe_state = p_first;
	dcp_cleaner(d->strlist);
	d->strlist = NULL;
	clean_cmda(d->cmds);
	d->cmds = NULL;
	d->pipe_n = 0;
	d->curr_pipe = 0;
}

//printf("rl: %s\n", rl);
//print_strlist(data->strlist);
//print_cmda(data->cmds);
static void	waiting_for_input(t_env *env, t_data *data)
{
	char	*rl;

	while (data->is_exiting == false)
	{
		reset_singleton(data);
		rl = readline("minishell $> ");
		if (!rl)
		{
			printf("exi>t\n");
			data->ret_status = 0;
			data->is_exiting = true;
			continue ;
		}
		add_history(rl);
		if (lexer(rl, env, data) == NULL)
			continue ;
		if (create_comm_list(data) == false)
			continue ;
		if (exec_comm_list(data) == false)
			continue ;
	}
	reset_singleton(data);
}

//need to figure out how to clean t_data data
int	main(int argc, char **argv, char **envp)
{
	t_env		*env;
	t_data		data;

	(void)argv;
	if (argc > 1)
		return (ft_putstr_fd("Algo de errado nao esta certo\n", 2), 1);
	g_sig = 0;
	set_signals_base();
	env = create_env_struct(envp);
	data = (t_data){-1, .envp = envp, env, .stdin = dup(0), dup(1)};
	waiting_for_input(env, &data);
	close(data.stdin);
	close(data.stdout);
	clear_env_struct(env);
	rl_clear_history();
	exit(data.ret_status);
}
