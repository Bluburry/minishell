/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printhexa.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 19:32:55 by tpinto-e          #+#    #+#             */
/*   Updated: 2023/03/03 18:52:04 by tpinto-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_puthexa(unsigned int nb, char *base)
{
	if (nb >= 16)
	{
		ft_puthexa(nb / 16, base);
		ft_puthexa(nb % 16, base);
	}
	else
		ft_putchar_fd(base[nb], 1);
}

int	ft_print_hexa(char c, unsigned int num)
{
	int	cnt;

	cnt = 0;
	if (!num)
		cnt++;
	if (c == 'X')
		ft_puthexa(num, "0123456789ABCDEF");
	else
		ft_puthexa(num, "0123456789abcdef");
	while (num)
	{
		cnt++;
		num /= 16;
	}
	return (cnt);
}
