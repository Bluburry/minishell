/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_args2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: remarque <remarque@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 14:40:57 by remarque          #+#    #+#             */
/*   Updated: 2024/01/10 14:40:58 by remarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// counts how many arguments there are in a phrase
// ignores the first word int the phrase since it's an executable
// ignores >, <, >>, << and the word following it
// returns the number of args for the program to be executed
// the list needs to be passed as the correct adress
// e.g. count_args(&list[5], 5) to count the arguments starting from the 6th idx
uint32_t	count_args(char **l, uint32_t n)
{
	uint32_t	i;
	uint32_t	count;

	i = 0;
	count = 0;
	while (i < n)
	{
		if (ft_strncmp(">", l[i], 1) == 0 || ft_strncmp("<", l[i], 1) == 0
			|| ft_strncmp(">>", l[i], 2) == 0 || ft_strncmp("<<", l[i], 2) == 0)
			i++;
		else
			count++;
		i++;
	}
	return (count);
}
