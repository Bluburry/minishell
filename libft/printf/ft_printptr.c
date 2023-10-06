/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printptr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 22:16:23 by tpinto-e          #+#    #+#             */
/*   Updated: 2023/03/03 18:52:44 by tpinto-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_printptr(unsigned long nb, char *base)
{
	if (nb >= 16)
	{
		ft_printptr(nb / 16, base);
		ft_printptr(nb % 16, base);
	}
	else
		ft_putchar_fd(base[nb], 1);
}

int	ft_ptr_helper(unsigned long num)
{
	int	cnt;

	cnt = 0;
	ft_printptr(num, "0123456789abcdef");
	while (num)
	{
		cnt++;
		num /= 16;
	}
	return (cnt);
}

int	ft_print_ptr(unsigned long hex)
{
	if (!hex)
		return (write(1, "(nil)", 5));
	ft_putstr_fd("0x", 1);
	return (2 + ft_ptr_helper(hex));
}
