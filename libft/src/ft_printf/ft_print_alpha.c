/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: remarque <remarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 19:16:24 by remarque          #+#    #+#             */
/*   Updated: 2023/04/17 20:11:36 by remarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_print_char(va_list args, t_p_data *pd)
{
	char	c;
	int		padding;

	c = va_arg(args, int);
	padding = pd->width - 1;
	while (padding > 0 && pd->dash == false)
	{
		pd->total_printed += write(pd->fd, &" ", 1);
		padding--;
	}
	pd->total_printed += write(pd->fd, &c, 1);
	while (padding > 0 && pd->dash == true)
	{
		pd->total_printed += write(pd->fd, &" ", 1);
		padding--;
	}
	reset_print_data(pd);
}

static inline void	ft_actually_print_string(char *str, t_p_data *pd)
{
	int		padding;
	size_t	nbytes;

	nbytes = ft_strlen(str);
	if (pd->has_dot == true && pd->precision < nbytes)
		nbytes = pd->precision;
	padding = pd->width - nbytes;
	while (padding > 0 && pd->dash == false)
	{
		pd->total_printed += write(pd->fd, &" ", 1);
		padding--;
	}
	pd->total_printed += write(pd->fd, str, nbytes);
	while (padding > 0 && pd->dash == true)
	{
		pd->total_printed += write(pd->fd, &" ", 1);
		padding--;
	}
	reset_print_data(pd);
}

void	ft_print_string(va_list args, t_p_data *pd)
{
	char	*str;

	str = va_arg(args, char *);
	if (!str)
	{
		if (pd->has_dot == true && pd->precision < 6)
			ft_actually_print_string("", pd);
		else
			ft_actually_print_string("(null)", pd);
	}
	else
		ft_actually_print_string(str, pd);
}
