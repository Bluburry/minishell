/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-e <tpinto-e@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 20:43:46 by tpinto-e          #+#    #+#             */
/*   Updated: 2024/01/11 20:43:47 by tpinto-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline bool	is_not_a_number(char *str)
{
	uint32_t	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (true);
		i++;
	}
	return (false);
}

bool	ft_exit(t_data *d, char **list)
{
	if (list_len(list) == 1)
		d->ret_status = 0;
	else if (is_not_a_number(list[1]))
	{
		printf("ERROR: Numeric argument required.\n");
		d->ret_status = 1;
	}
	else if (list_len(list) > 2)
		return (printf("Error: Too many arguments.\n"), false);
	else
		d->ret_status = ft_atoi(list[1]);
	d->is_exiting = true;
	return (true);
}
