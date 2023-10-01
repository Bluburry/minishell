/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 19:30:46 by tpinto-e          #+#    #+#             */
/*   Updated: 2022/12/01 21:25:18 by tpinto-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_atoi(const char *nptr)
{
	int	number;
	int	i;

	number = 0;
	i = 1;
	while (*nptr == 32 || (*nptr >= 9 && *nptr <= 13))
		nptr++;
	if (*nptr == '-')
	{
		i *= -1;
		nptr++;
	}
	else if (*nptr == '+')
		nptr++;
	while (*nptr != '\0' && *nptr <= 57 && *nptr >= 48)
	{
		number *= 10;
		number += *nptr - 48;
		nptr++;
	}
	return (number * i);
}
