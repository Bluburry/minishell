#include "minishell.h"

bool	fill_tree(t_data *data);

bool	create_tree(t_data *data)
{
	uint32_t	i;

	i = 0;
	data->ast = create_ast(NULL, 64);
	if (data->ast == NULL || data->strlist == NULL)
		return (free(data->ast), free(data->strlist), false); // needs to be set to 0
	if (data->strlist[i])
	{
		if (ft_strncmp("exit", data->strlist[i], 4) == 0)
			insert_node(data->ast, (t_tok){.type = exit_b}, 0);
	}
	return (true);
}
