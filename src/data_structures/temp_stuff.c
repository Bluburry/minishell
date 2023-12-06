/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: remarque <remarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 13:40:31 by remarque          #+#    #+#             */
/*   Updated: 2023/11/06 14:14:29 by remarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <stdint.h>

void	go_through_string_list(t_ast *ast, char **list)
{
	uint32_t	i;

	i = 0;
	while (list[i])
	{
		if (ft_strncmp(list[i], "exit", 4))
			insert_node(ast, (t_tok){exit_b, NULL, NULL}, 0);
		i++;
	}
}

#define CAP 64
void	fill_ast(char **list)
{
	t_ast	*ast;

	ast = create_ast(NULL, CAP);
	if (ast == NULL)
		return ;
	go_through_string_list(ast, list);

}

// ok, in order to create tokens from the strings, I need to go through the 
// list and check for stuff
t_tok	token_from_string(char *str)
{
	if (ft_strncmp("exit", str, 5))
		return ((t_tok){exit_b, NULL, NULL});
	return ((t_tok){none, NULL, NULL});
}

typedef struct s_pipe
{
	int		prevfd;
	int		ret_status;
}	t_pipe;

typedef struct s_singleton
{
	int		in;
	int		ret_status;
	bool	start;
	bool	end;
	char	*path;
	char	**argv;
	char	*env[];
}	t_singleton;

int	inner_pipe(int in, int out, char *path, char *argv[], char *env[])
{
	int	pid;
	int	status;

	status = 0;
	pid = fork();
	if (pid == 0)
	{
		dup2(out, STDOUT_FILENO);
		close(out);
		dup2(in, STDIN_FILENO);
		close(in);
		execve(path, argv, env);
	}
	else
	{
		close(out);
		waitpid(pid, &status, 0);
	}
	return (WEXITSTATUS(status));
}

// flag is 0 means its in the middle
// flag as 1 means its in the start
// flag as 2 means its in the end
t_pipe	mid_pipe(uint32_t flag, int prevfd, char *path, char *argv[], char *env[])
{
	int	fd[2];
	int	in;
	int	out;

	if (flag == 2)
	{
		in = prevfd;
		out = STDOUT_FILENO;
	}
	else
		if (pipe(fd) == -1)
			return ((t_pipe){-1, -1});
	if (flag == 1)
	{
		in = STDIN_FILENO;
		out = fd[1];
	}
	else
	{
		in = prevfd;
		out = fd[1];
	}
	return ((t_pipe){fd[0],inner_pipe(in, out, path, argv, env)});
}//fd[0] is always returned as prevfd

//maybe i need some sort of singleton to track the state of prevfd across uses
//less maybe and more definitely
//this singleton would need to be created at the start of parsing, and would
//survive until the end of it
//basically, it's a big blob of state
void outer_pipe(t_singleton *s)
{
	t_pipe	pipe;
	int		flag;

	if (s->start)
		flag = 1;
	else if (s->end)
		flag = 2;
	else
		flag = 0;
	pipe = mid_pipe(flag, s->in, s->path, s->argv, s->env);
	s->in = pipe.prevfd;
	s->ret_status = pipe.ret_status;
	if (s->end)
	{
		close(s->in);
		s->in = -1;
	}
}
