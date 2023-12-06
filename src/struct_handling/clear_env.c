#include "minishell.h"

/**
 * @brief removes an environmental variable from the strucutre
 * @param env structure
 * @param var variable to remove
*/
void	unset_env_var(t_env *env, char *var)
{
	int		i;
	char	**temp_var;

	i = index_of_str(env, var);
	if (i >= env->size)
		return ;
	temp_var = env->vars;
	env->vars = (char **) malloc(sizeof(char *) * env->capacity);
	copy_char_matrix(temp_var, env->vars, env->size, i);
	clear_chars(temp_var, env->size);
	env->size--;
}

/**
 * @brief frees an array of strings with a given size, 
 * pass -1 if size is to be ignored, the function will then 
 * free until a null pointer
 * @param str array of strings to free
 * @param size size of array
*/
void	clear_chars(char **str, int size)
{
	int	i;

	i = 0;
	while ((size == -1 && str[i]) || i < size)
	{
		free(str[i++]);
	}
	free(str);
}

/**
 * @brief frees env structure from memory
 * @param env t_env structure to free
*/
void	clear_env_struct(t_env *env)
{
	clear_chars(env->vars, env->size);
	free(env);
}
