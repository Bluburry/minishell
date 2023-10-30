#include "minishell.h"

/**
 * @brief counts how many environmental variables there are
 * @param envp char** argument passed to main
 * @return number of environmental variables
*/
int	get_env_start_size(char **envp)
{
	int	size;

	size = 0;
	while (*envp)
	{
		size++;
		envp++;
	}
	return (size);
}

/**
 * @brief populates a new array of strings by copying another one, 
 * the option to skip an index is available (useful for unset), 
 * if this is not needed simply pass -1 to the skip parameter
 * @param mat matrix to copy
 * @param new_mat destination matrix
 * @param size size of matrix to copy
 * @param skip index to skip, -1 if not necessary
*/
void	copy_char_matrix(char **mat, char **new_mat, int size, int skip)
{
	int		i;
	int		j;
	size_t	s;

	i = 0;
	j = 0;
	while (i < size)
	{
		if (i == skip)
		{
			i++;
			continue ;
		}
		s = ft_strlen(mat[i]) + 1;
		new_mat[j] = (char *) malloc(sizeof(char) * s);
		ft_memcpy(new_mat[j], mat[i], s);
		i++;
		j++;
	}
}

/**
 * @brief takes the main argument envp and returns
 * a t_env struct, which functions as a dynamic array
 * @param envp char** argument passed to main
 * @return t_env*
*/
t_env	*create_env_struct(char **envp)
{
	t_env	*env;

	env = (t_env *) malloc(sizeof(t_env));
	env->size = get_env_start_size(envp);
	env->capacity = env->size + 20;
	env->vars = (char **) malloc(sizeof(char *) * env->capacity);
	copy_char_matrix(envp, env->vars, env->size, -1);
	return (env);
}
