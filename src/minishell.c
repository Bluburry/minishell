#include "minishell.h"
#include "structures.h"
#include <stdint.h>

/* void	waiting_for_input(t_env *env)
{
	char	*rl;
	int		id;
	int		fd[2];
	int		len;

	pipe(fd);
	while (1)
	{
		id = fork();
		if (id == 0)
		{
			//open(fd[1]);
			rl = readline("minishell -> ");
			len = strlen(rl) + 1;
			write(fd[1], &len, sizeof(int));
			write(fd[1], rl, len);
			printf("rl: %s\n", rl);
			lexer(rl, env);
			//close(fd[1]);
			exit (0);
		}
		else
		{
			waitpid(id, NULL, 0);
			read(fd[0], &len, sizeof(int));
			rl = malloc(len * sizeof(char));
			read(fd[0], rl, len * sizeof(int));
			add_history(rl);
		}
	}
} */

static void	print_strlist(char **list)
{
	uint32_t	i;

	i = 0;
	while (list[i])
	{
		if (list[i][0] == 31)
			printf("HERE IS QUOTES:\n");
		printf("%s\n", list[i++]);
	}
}

static void	print_cmda(t_cmda *cmds)
{
	const char	*strs[7] = {"NONE", "EXEC", "PIPE", "OUT", "IN", "APPEND", "HEREDOC"};

	if (!cmds->tks)
		return ;
	for (uint32_t i = 0; i < cmds->size; i++)
	{
		printf("%d %s : \"%s\"",cmds->tks[i].type, strs[cmds->tks[i].type], cmds->tks[i].path);
		if (cmds->tks[i].arglist) {
			printf(" :");
			for (uint32_t j = 0; cmds->tks[i].arglist[j]; j++)
				printf(" \"%s\"", cmds->tks[i].arglist[j]);
		}
		printf("\n");
	}
}

void	waiting_for_input(t_env *env, t_data *data)
{
	char	*rl;

	while (data->is_exiting == false)
	{
		dcp_cleaner(data->strlist);
		data->strlist = NULL;
		clean_cmda(data->cmds);
		data->cmds = NULL;
		rl = readline("minishell > ");
		if (!rl)
		{
			printf("exit\n");
			data->is_exiting = true;
			continue ;
		}
		printf("rl: %s\n", rl);
		add_history(rl);
		if (lexer(rl, env, data) == NULL)
			continue ;
		print_strlist(data->strlist);
		if (create_comm_list(data) == false)
			continue ;
		print_cmda(data->cmds);
		if (exec_comm_list(data) == false)
			continue ;
		dcp_cleaner(data->strlist);
		data->strlist = NULL;
		clean_cmda(data->cmds);
		data->cmds = NULL;
	}
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
	//ioctl(STDIN_FILENO, CTRL_D, ...);
	init_signals();
	env = create_env_struct(envp);
	data = (t_data){.envp = envp, env};
	waiting_for_input(env, &data);
	clear_env_struct(env);
	rl_clear_history();
}

/* add_new_env_var(env, "TEST=24");
	add_new_env_var(env, "TEST2");
	add_new_env_var(env, "TEST3=");
	unset_env_var(env, "TEST");
	int i = -1;
	while (++i < env->size)
	{
		printf("%s\n", env->vars[i]);
	}
	printf("\n\nSearch LANG: %s\n", get_env_var(env, "LANG"));
	printf("\n\nSearch PWD: %s\n", get_env_var(env, "PWD"));
	printf("\n\nSearch LS_COLORS: %s\n", get_env_var(env, "LS_COLORS"));
	printf("\n\nSearch LSCOLORS: %s\n", get_env_var(env, "LSCOLORS"));
	printf("\n\nSearch MAKEFLAGS: %s\n", get_env_var(env, "MAKEFLAGS"));
	printf("\n\nSearch SHLVL: %s\n", get_env_var(env, "SHLVL"));
	printf("\n\nSearch TEST: %s\n", get_env_var(env, "TEST"));
	add_new_env_var(env, "TEST=42");
	printf("\n\nSearch TEST: %s\n", get_env_var(env, "TEST"));
	printf("\n\nSearch TEST2: %s\n", get_env_var(env, "TEST2"));
	printf("\n\nSearch TEST3: %s\n", get_env_var(env, "TEST3"));
	add_new_env_var(env, "TEST4=169");
	char **test = env_string(env);
	printf("\n\ntest env_string:\n");
	i = -1;
	int n = num_invalid_env_vars(env);
	while (++i < env->size - n)
	{
		printf("%s\n", test[i]);
	}
	clear_chars(test, env->size - n); 
	printf("\n\ntest export_string:\n");
	test = export_string(env);
	i = -1;
	while (++i < env->size)
	{
		printf("%s\n", test[i]);
	}
	clear_chars(test, env->size); */
	//char *cwd;
	//cwd = pwd();
	//printf("pwd: %s\n", cwd);
	//free(cwd);
	//printf("cd Desktop:\n");
	//printf("cd ~:\n");
	//cd(env, "~");
	//cwd = pwd();
	//printf("pwd: %s\n", cwd);
	//free(cwd);
	/*printf("cd include:\n");
	cd(env, "include");
	printf("cd ../:\n");
	cd(env, "../");
	printf("cd Minishell:\n");
	cd(env, "Minishell");
	printf("cd ../include:\n");
	cd(env, "../include");
	printf("cd ../minishell:\n");
	cd(env, "../minishell");
	printf("cd ./include:\n");
	cd(env, "./include");
	printf("cd ../../minishell:\n");
	cd(env, "../../minishell");
	printf("cd :\n");
	cd(env, "");
	printf("cd ~/:\n");
	cd(env, "~/");
	printf("cd Desktop:\n");
	cd(env, "Desktop");
	printf("cd ~/Desktop:\n");
	cd(env, "~/Desktop");
	printf("cd Minishell:\n");
	cd(env, "Minishell");
	printf("cd ..:\n");
	cd(env, "..");
	printf("cd ~/..:\n");
	cd(env, "~/..");
	printf("cd asdasd:\n");
	cd(env, "asdasd");
	cd(env, "/home/");
	cd(env, "~/")
	//waiting_for_input(env);*/
	/*char *test;
	test = find_exe_path(get_env_var(env, "PATH"), "cat");
	printf("%s\n", test);
	free(test);
	test = find_exe_path(get_env_var(env, "PATH"), "tac");
	printf("%s\n", test);
	free(test);
	test = find_exe_path(get_env_var(env, "PATH"), "tic");
	printf("%s\n", test);
	free(test);
	test = find_exe_path(get_env_var(env, "PATH"), "donkey");
	if (test == NULL) printf("hi\n");
	else
	{
		printf("%s\n", test);
		free(test);
	}
	clear_env_struct(env);
	rl_clear_history();
	return (0);
}*/
