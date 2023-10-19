#include "../../include/minishell.h"

/**
 * @brief replaces an environmental variable in position i 
 * of the string array with the new string
 * @param env environmental variable structure
 * @param new string to copy
 * @param i index of string to replace
*/
void	alter_env_var(t_env *env, const char *new, int i)
{
	int	s;

	s = ft_strlen(new) + 1;
	free(env->vars[i]);
	env->vars[i] = (char *) malloc(s * sizeof(char));
	ft_memcpy(env->vars[i], new, s);
}

/**
 * @brief checks if a string already exists in the environmental variables 
 * by comparing it up to '=' with the already existing ones
 * @param env structure that hold the environmental variables
 * @param new string to find
 * @return returns 0 if the new variable doesn't already exists, otherwise 
 * return the index in the array where it is stored
*/
int	env_already_exists(t_env *env, const char *new)
{
	int	i;
	int	j;

	i = -1;
	while (++i < env->size)
	{
		j = 0;
		while (env->vars[i][j] && env->vars[i][j] == new[j] \
			&& env->vars[i][j] != '=' && new[j] != '=')
			j++;
		if (env->vars[i][j] == '=' && new[j] == '=')
			return (i);
	}
	return (-1);
}

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
	copy_char_matrix(old_vars, env->vars, env->size, -1);
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
	int		i;

	i = env_already_exists(env, new);
	if (i >= 0)
	{
		alter_env_var(env, new, i);
		return ;
	}
	if (env->size == env->capacity)
		resize_env_struct(env);
	s = ft_strlen(new) + 1;
	env->vars[env->size] = (char *) malloc(sizeof(char *) * s);
	ft_memcpy(env->vars[env->size], new, s);
	env->size++;
}
