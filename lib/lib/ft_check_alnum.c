/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_alnum.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 15:10:28 by tpinto-e          #+#    #+#             */
/*   Updated: 2023/03/22 17:14:44 by tpinto-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	check_negative(char *str)
{
	int	neg_count;
	int	i;

	i = -1;
	neg_count = 0;
	while (str[++i] != 0)
		if (str[i] == '-')
			neg_count++;
	if (neg_count > 1)
		return (0);
	else
		return (1);
}

int	ft_check_alnum(char *str)
{
	if (*str == '-')
	{
		if (!check_negative(str))
			return (0);
		else
			str++;
	}
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}
