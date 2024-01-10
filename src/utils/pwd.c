/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecarval <jecarval@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 14:41:47 by remarque          #+#    #+#             */
/*   Updated: 2024/01/10 14:50:07 by jecarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief gets the current working directory by using 
 * getcwd, the returning string must be freed
 * @return current working directory, needs to be freed 
 * can be NULL if there was an error
*/
char	*pwd(void)
{
	char	*cwd;

	cwd = NULL;
	cwd = getcwd(cwd, PATH_MAX);
	return (cwd);
}
