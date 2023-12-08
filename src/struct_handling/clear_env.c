#include "minishell.h"

void	copy_char_matrix_skip(char **mat, char **new_mat, char **skip)
{
	int		i;
	int		j;
	int		k;
	size_t	s;

	i = 0;
	j = 0;
	while (i < env->size)
	{
		k = 0;
		while (skip[k] != NULL)
		{
			if (ft_strchrstr(mat[i], '=', skip[k]))
			{
				i++;
				continue;
			}
		}
		s = ft_strlen(mat[i]) + 1;
		new_mat[j] = (char *) malloc(sizeof(char) * s);
		ft_memcpy(new_mat[j], mat[i], s);
		i++;
		j++;
	}
}

/**
 * @brief removes an environmental variable from the strucutre
 * @param env structure
 * @param var variable to remove
*/
// preciso alterar para considerar varias novas vars ao mesmo tempo, ie: char **
void	unset_env_var(t_env *env, char **var)
{
	int		i;
	char	**temp_var;

	temp_var = env->vars;
	env->vars = (char **) malloc(sizeof(char *) * env->capacity);
	copy_char_matrix(temp_var, env->vars, skip);
	clear_chars(temp_var, env->size);
	i = 0;
	while (vars[i] != NULL)
		i++;
	env->size -= i;
	i = env->size;
	while (i < env->capacity)
		env->vars[i++] = NULL;
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
