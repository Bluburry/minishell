#include "minishell.h"

bool	traverse_tree(t_data *data)
{
	if (data->ast == NULL)
		return (false);
	if (data->ast->tokens[0].type == exit_b)
		data->is_exiting = true;
	return (true);
}
