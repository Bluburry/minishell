#include "../../include/minishell.h"

/**
 * @brief resize the char matrix in the env structure
 * @param env structure
*/
void	resize_env_struct(t_env *env)
{
	char	**new_vars;

	new_vars = (char **) malloc(sizeof(char *) * env->capacity + 20);
	copy_char_matrix(env->vars, new_vars, env->capacity);
	clear_chars(env->vars, env->capacity);
	env->vars = new_vars;
	env->capacity += 20;
}

/**
 * @brief adds a new environmental variable to the structure, 
 * resizing if necessary
 * @param new new string to add
*/
void	add_new_env_var(t_env *env, char *new)
{
	size_t	s;

	if (env->size == env->capacity)
		resize_env_struct(env);
	s = ft_strlen(new) + 1;
	env->size++;
	env->vars[env->size] = (char *) malloc(sizeof(char *) * s);
	ft_memcpy(env->vars[env->size], new, s);
}
