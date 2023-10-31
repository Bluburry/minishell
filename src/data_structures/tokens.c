/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: remarque <remarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 13:40:31 by remarque          #+#    #+#             */
/*   Updated: 2023/10/31 15:40:28 by remarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <stdint.h>

// an enum that decides wether the token is a name or an operator
typedef enum e_etok
{
	none,
	exec,
	r_pipe,
	r_out,
	r_in,
	r_append,
	r_heredoc,
}	t_etok;

// a token read by the parser, with the optional path and list of arguments
// used by exec
typedef struct s_tok
{
	t_etok		type;
	char		*path;
	char		**arglist;
}	t_tok;

// dynamically allocated list of tokens
typedef struct s_ast
{
	t_tok		*tokens;
	uint32_t	cap;
}	t_ast;

// creates a new resource of size size, copies the contents of ptr into it
// and returns the new resource while freeing ptr
void	*ft_reallocation(void *ptr, size_t ptrsize, size_t size)
{
	char		*temp;
	uint32_t	i;

	if (ptr == NULL)
		return (malloc(size));
	if (size == 0)
		return (free(ptr), NULL);
	temp = malloc(size);
	if (temp == NULL)
		return (NULL);
	i = 0;
	while (i < ptrsize)
	{
		temp[i] = ((char *)ptr)[i];
		i++;
	}
	return (free(ptr), temp);
}

// Creates the abstract syntax tree used to organise the tokens
t_ast	*create_ast(t_tok *tokens, uint32_t cap)
{
	t_ast	*ast;

	ast = malloc(sizeof(t_ast));
	if (ast == NULL)
		return (NULL);
	*ast = (t_ast){0, cap};
	if (tokens == NULL)
	{
		ast->tokens = malloc(sizeof(t_tok) * cap);
		if (ast->tokens == NULL)
			return (free(ast), NULL);
	}
	else
		ast->tokens = tokens;
	return (ast);
}

void	clean_token_contents(t_tok *token)
{
	uint32_t	i;

	token->type = none;
	i = 0;
	if (token->arglist != NULL)
		while (token->arglist[i])
			free(token->arglist[i++]);
	free(token->arglist);
	token->arglist = NULL;
	free(token->path);
	token->path = NULL;
}

void	clean_ast(t_ast *ast)
{
	uint32_t	i;

	if (ast->tokens != NULL)
	{
		i = 0;
		while (i < ast->cap)
			clean_token_contents(&ast->tokens[i++]);
		free(ast->tokens);
	}
	free(ast);
}

void	insert_node(t_ast *ast, t_tok tok, uint32_t i)
{
	if (i >= ast->cap)
		ast = ft_reallocation(ast, ast->cap, ast->cap * 2);
	ast->tokens[i] = tok;
}

void remove_node(t_ast *ast, uint32_t i)
{
	clean_token_contents(&ast->tokens[i]);
}

t_tok	*token_from_string(char *str)
{
	if (ft_strncmp(const char *s1, const char *s2, size_t n))
}

//my AST needs to be able to tell if a pipe chain is in the start, middle or end

typedef struct s_pipe
{
	int		prevfd;
	int		ret_status;
	// char	*path;
	// char	**argv;
	// char	*env[];
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
