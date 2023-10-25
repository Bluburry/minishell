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
 * @brief populates the vars value of the t_env structure by copying 
 * all the string found in envp
 * @param mat matrix to copy
 * @param new_mat destination matrix
 * @param size size of matrix to copy
*/
void	copy_char_matrix(char **mat, char **new_mat, int size)
{
	int		i;
	size_t	s;

	i = 0;
	while (i < size)
	{
		s = ft_strlen(mat[i]) + 1;
		new_mat[i] = (char *) malloc(sizeof(char) * s);
		ft_memcpy(new_mat[i], mat[i], s);
		i++;
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
	copy_char_matrix(envp, env->vars, env->size);
	return (env);
}
