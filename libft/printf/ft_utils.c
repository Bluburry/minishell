/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 18:52:39 by tpinto-e          #+#    #+#             */
/*   Updated: 2023/03/03 18:59:19 by tpinto-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_print_str(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (write(1, "(null)", 6));
	while (str[i])
	{
		ft_putchar_fd(str[i], 1);
		i++;
	}
	return (i);
}

int	ft_print_uns_dec(unsigned int nbr)
{
	int	cnt;

	if (nbr <= 2147483647)
		ft_putnbr_fd(nbr, 1);
	else
	{
		ft_print_uns_dec(nbr / 10);
		ft_putnbr_fd(nbr % 10, 1);
	}
	cnt = 0;
	if (!nbr)
		cnt++;
	while (nbr)
	{
		cnt++;
		nbr /= 10;
	}
	return (cnt);
}

int	ft_print_dec(int nbr)
{
	int	cnt;

	ft_putnbr_fd(nbr, 1);
	cnt = 0;
	if (!nbr)
		cnt++;
	else if (nbr < 0)
	{
		cnt++;
		nbr *= -1;
	}
	while (nbr)
	{
		cnt++;
		nbr /= 10;
	}
	return (cnt);
}
