#include "../../include/minishell.h"

/**
 * @brief frees an array of strings with a given size
 * @param str array of strings to free
 * @param size size of array
*/
void	clear_chars(char **str, int size)
{
	int	i;

	i = -1;
	while (++i < size)
	{
		free(str[i]);
	}
}

/**
 * @brief frees env structure from memory
 * @param env t_env structure to free
*/
void	clear_env_struct(t_env *env)
{
	clear_chars(env->vars, env->size);
	free(env->vars);
	free(env);
}
