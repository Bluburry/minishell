/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alter_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: remarque <remarque@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 14:41:18 by remarque          #+#    #+#             */
/*   Updated: 2024/01/10 14:41:18 by remarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief replaces an environmental variable in position i 
 * of the string array with the new string
 * @param env environmental variable structure
 * @param new string to copy
 * @param i index of string to replace
*/
void	replace_env_var(t_env *env, const char *new, int i)
{
	int	s;

	s = ft_strlen(new) + 1;
	free(env->vars[i]);
	env->vars[i] = (char *) malloc(s * sizeof(char));
	ft_memcpy(env->vars[i], new, s);
}

/**
 * @brief resize the char matrix in the env structure
 * @param env structure
 * @param inc size to increment
*/
static void	resize_env_struct(t_env *env, int inc)
{
	char	**old_vars;
	int		i;

	old_vars = env->vars;
	env->capacity += inc;
	env->vars = (char **) malloc(sizeof(char *) * env->capacity);
	copy_char_matrix(old_vars, env->vars, env->size);
	clear_chars(old_vars, env->size);
	i = env->size - 1;
	while (++i < env->capacity)
		env->vars[i] = NULL;
}

/**
 * @brief compares all the established environmental variables with 
 * the new strings, if they're equal then the old env var is altered 
 * otherwise the new var is added
 * @param env environment structure
 * @param new strings to add/alter
*/
static void	env_var_checkup(t_env *env, char **new)
{
	int		i;
	int		j;
	int		t;
	size_t	s;

	i = 0;
	t = env->size;
	while (new[++i])
	{
		j = -1;
		while (++j < t)
		{
			if (ft_strchrstr(new[i], '=', env->vars[j]))
			{
				replace_env_var(env, new[i], j);
				break ;
			}
		}
		if (j < t)
			continue ;
		s = ft_strlen(new[i]) + 1;
		env->vars[env->size] = (char *) malloc(sizeof(char) * s);
		ft_memcpy(env->vars[env->size], new[i], s);
		env->size++;
	}
}

/**
 * @brief checks if the new env var is valid, they must start 
 * with a letter, and can only contain numbers and letters
 * @return 1 if the string is valid, 0 otherwise, printing
 * a message displaying the incorrect string
 */
static int	check_valid_var(char *str)
{
	int	i;

	i = 0;
	if (!str || !((str[i] >= 65 && str[i] <= 90) || \
		(str[i] >= 97 && str[i] <= 122)))
	{
		printf("\nexport: \'%s\': not a valid identifier\n", str);
		return (0);
	}
	while (str[i] && str[i] != '=')
	{
		if (!((str[i] >= 'A' && str[i] <= 'Z') || \
			(str[i] >= 'a' && str[i] <= 'z') || \
			(str[i] >= '0' && str[i] <= '9') || str[i] == '_'))
		{
			printf("\nexport: \'%s\': not a valid identifier\n", str);
			return (0);
		}
		i++;
	}
	return (1);
}

/**
 * @brief adds a new environmental variable to the structure, 
 * resizing if necessary
 * @param new new string to add
*/
int	alter_env_var(t_env *env, char **new)
{
	int		s;

	s = 0;
	while (new[++s])
		if (!check_valid_var(new[s]))
			return (0);
	if (env->size + s >= env->capacity)
	{
		if (s < 20)
			s = 20;
		resize_env_struct(env, s);
	}
	env_var_checkup(env, new);
	return (1);
}
