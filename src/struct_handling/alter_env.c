#include "minishell.h"

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
	int		i;

	old_vars = env->vars;
	env->capacity += 20;
	new_vars = (char **) malloc(sizeof(char *) * env->capacity);
	env->vars = new_vars;
	copy_char_matrix(old_vars, env->vars, env->size);
	clear_chars(old_vars, env->size);
	i = env->size - 1;
	while (++i < env->capacity)
		env->vars[i] = NULL;
}

/**
 * @brief checks if a new env var is valid, 
 * it must start with a letter, and can only contain 
 * numbers and letters
 */
char	*check_valid_var(const char **str)
{
	while (*str)
	{
		if (!str || !*str || \
			!((*str >= 65 && *str <= 90) ||
				(*str >= 97 && *str <= 122)))
			return (0);
		while (*str && *str != '=')
		{
			if (!((*str >= 65 && *str <= 90) ||
					(*str >= 97 && *str <= 122) ||
					(*str >= 48 && *str <= 57)))
				return (0);
			str++;
		}
		str++;
	}
	return (1);
}

/**
 * @brief adds a new environmental variable to the structure, 
 * resizing if necessary
 * @param new new string to add
*/
// preciso alterar para considerar varias novas vars ao mesmo tempo, ie: char **
int	add_new_env_var(t_env *env, const char **new)
{
	size_t	s;
	char	*str;
	int		i;

	str = check_valid_var(new);
	if (str)
	{
		printf("\nexport: \'%s\': not a valid identifier\n", str);
		return (0);
	}
	i = env_already_exists(env, new);
	if (i >= 0)
	{
		alter_env_var(env, new, i);
		return (1);
	}
	if (env->size == env->capacity)
		resize_env_struct(env);
	s = ft_strlen(new) + 1;
	env->vars[env->size] = (char *) malloc(sizeof(char *) * s);
	ft_memcpy(env->vars[env->size], new, s);
	env->size++;
	return (1);
}
