/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: remarque <remarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 13:40:31 by remarque          #+#    #+#             */
/*   Updated: 2023/10/25 17:11:13 by remarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	char		*arglist[];
}	t_tok;

// dynamically allocated list of tokens
typedef struct s_ast
{
	t_tok		*tokens;
	uint32_t	size;
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
t_ast	*create_ast(t_tok *tokens, uint32_t cap, uint32_t size)
{
	t_ast	*ast;

	ast = malloc(sizeof(t_ast));
	if (ast == NULL)
		return (NULL);
	*ast = (t_ast){0, size, cap};
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

	free(token->path);
	i = 0;
	while (token->arglist[i] != NULL)
	{
		free(token->arglist[i]);
		i++;
	}
	free(token->arglist);
}

void	clean_ast(t_ast *ast)
{
	uint32_t	i;

	if (ast->tokens != NULL)
	{
		i = 0;
		while (i < ast->cap)
			clean_token_contents(&ast->tokens[i]);
		free(ast->tokens);
	}
	free(ast);
}

void insert_into_ast();

void remove_from_ast();