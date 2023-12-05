#include "minishell.h"

bool	traverse_tree(t_data *data)
{
	if (data->cmds == NULL)
		return (false);
	if (data->cmds->tks[0].type == exit_b)
		data->is_exiting = true;
	return (true);
}
