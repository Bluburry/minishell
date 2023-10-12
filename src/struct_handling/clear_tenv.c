#include "../../include/minishell.h"

void	clear_env_struct(t_env *env)
{
	int	i;

	i = -1;
	while (++i < env->size)
	{
		free(env->vars[i]);
	}
	free(env->vars);
	free(env);
}