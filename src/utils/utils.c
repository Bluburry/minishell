/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: remarque <remarque@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 14:41:57 by remarque          #+#    #+#             */
/*   Updated: 2024/01/10 14:41:58 by remarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief checks if passed string is a valid parameter
 * @param path string path to check
 * @return -1 if not a path, 0 if path, 1 if file
 */
int	check_path(char *path)
{
	struct stat	bs;
	int			ret;

	if (stat(path, &bs) == -1)
	{
		printf("Invalid directory.\n");
		ret = -1;
	}
	else
		ret = 0;
	if (ret != -1 && S_ISREG(bs.st_mode))
		ret = 1;
	return (ret);
}

bool	is_metachar(char c)
{
	if (c == '|' || c == '&' || c == ';' || c == '(' || c == ')' || c == '<'
		|| c == '>')
		return (true);
	return (false);
}

bool	is_name(char *str)
{
	size_t		size;

	if (str == NULL)
		return (false);
	size = ft_strlen(str);
	if (size == 1)
		if (is_metachar(str[0]))
			return (false);
	if (size == 2)
		if (is_metachar(str[0]) && is_metachar(str[1]))
			return (false);
	return (true);
}

//removes the initial character if it`s character \31
//character \31 is inserted inside strings as the first character
//when that string token originates within quotes
char	*remc(char *str)
{
	if (str[0] == 31)
		return (str + 1);
	return (str);
}

// counts the number of items in the string list
uint32_t	list_len(char **list)
{
	uint32_t	i;

	if (list == NULL)
		return (0);
	i = 0;
	while (list[i] != NULL)
		i++;
	return (i);
}
