#include "minishell.h"

// Creates the command array tree used to organise the tokens
t_cmda	*create_cmda(uint32_t cap)
{
	t_cmda	*cmda_arr;

	cmda_arr = malloc(sizeof(t_cmda));
	if (cmda_arr == NULL)
		return (NULL);
	*cmda_arr = (t_cmda){0, 0, cap};
	cmda_arr->tks = malloc(sizeof(t_tok) * cap);
	if (cmda_arr->tks == NULL)
		return (free(cmda_arr), NULL);
	return (cmda_arr);
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

// cleans the contents and frees the cmda as well its tokens array
void	clean_cmda(t_cmda *cmd_arr)
{
	uint32_t	i;

	if (cmd_arr->tks != NULL)
	{
		i = 0;
		while (i < cmd_arr->cap)
			clean_token_contents(&cmd_arr->tks[i++]);
		free(cmd_arr->tks);
	}
	free(cmd_arr);
}

// inserts a node with the token tok in the cmda at the position i
void	insert_node(t_cmda *cmd_arr, t_tok tok, uint32_t i) //kind of useless, delete later
{
	if (i >= cmd_arr->cap)
		cmd_arr = ft_reallocation(cmd_arr, cmd_arr->cap, cmd_arr->cap * 2);
	cmd_arr->tks[i] = tok;
}

//removes the node in the position i from the cmda
void	remove_node(t_cmda *cmd_arr, uint32_t i)
{
	clean_token_contents(&cmd_arr->tks[i]);
}
