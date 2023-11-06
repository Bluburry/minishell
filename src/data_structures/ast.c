#include "minishell.h"

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

// cleans the contents of a single token in a tokens array
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

// cleans the contents and frees the ast as well its tokens array
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

// inserts a node with the token tok in the ast at the position i
void	insert_node(t_ast *ast, t_tok tok, uint32_t i)
{
	if (i >= ast->cap)
		ast = ft_reallocation(ast, ast->cap, ast->cap * 2);
	ast->tokens[i] = tok;
}

//removes the node in the position i from the ast
void	remove_node(t_ast *ast, uint32_t i)
{
	clean_token_contents(&ast->tokens[i]);
}
