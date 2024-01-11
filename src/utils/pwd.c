/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-e <tpinto-e@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 20:43:51 by tpinto-e          #+#    #+#             */
/*   Updated: 2024/01/11 20:43:52 by tpinto-e         ###   ########.fr       */
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
