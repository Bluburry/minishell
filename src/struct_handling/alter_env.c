#include "../../include/minishell.h"

/**
 * @brief resize the char matrix in the env structure
 * @param env structure
*/
void	resize_env_struct(t_env *env)
{
	char	**new_vars;
	char	**old_vars;
	
	old_vars = env->vars;
	env->capacity += 20;
	new_vars = (char **) malloc(sizeof(char *) * env->capacity);
	env->vars = new_vars;
	copy_char_matrix(old_vars, env->vars, env->size);
	clear_chars(old_vars, env->size);
}

/**
 * @brief adds a new environmental variable to the structure, 
 * resizing if necessary
 * @param new new string to add
*/
void	add_new_env_var(t_env *env, const char *new)
{
	size_t	s;

	if (env->size == env->capacity)
		resize_env_struct(env);
	s = ft_strlen(new) + 1;
	env->vars[env->size] = (char *) malloc(sizeof(char *) * s);
	ft_memcpy(env->vars[env->size], new, s);
	env->size++;
}
