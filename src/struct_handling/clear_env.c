/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: remarque <remarque@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 14:41:21 by remarque          #+#    #+#             */
/*   Updated: 2024/01/10 14:41:22 by remarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief removes an environmental variable from the strucutre
 * @param env structure
 * @param var variables to remove
*/
int	unset_env_var(t_env *env, char **var)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (var[++i])
	{
		j = -1;
		while (++j < env->size)
		{
			if (ft_strchrstr(env->vars[j], '=', var[i]))
			{
				free(env->vars[j]);
				env->vars[j] = NULL;
				env->size--;
				tmp = env->vars[env->size];
				env->vars[env->size] = env->vars[j];
				env->vars[j] = tmp;
				break ;
			}
		}
	}
	return (0);
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
