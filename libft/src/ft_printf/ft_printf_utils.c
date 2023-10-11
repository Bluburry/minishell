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

void	reset_print_data(t_p_data *pd)
{
	pd->width = 0;
	pd->precision = 0;
	pd->has_dot = false;
	pd->pound = false;
	pd->plus_sign = false;
	pd->zero_padding = false;
	pd->dash = false;
	pd->space = false;
	pd->is_negative = false;
	pd->is_uint = false;
	pd->is_upper = false;
}

size_t	print_argument(va_list args, const char *fmt, t_p_data *pd, size_t i)
{
	if (fmt[i] == 'c')
		ft_print_char(args, pd);
	else if (fmt[i] == 's')
		ft_print_string(args, pd);
	else if (fmt[i] == 'p')
		ft_print_pointer(args, pd);
	else if (fmt[i] == 'd' || fmt[i] == 'i')
		ft_print_signed_dec(args, pd);
	else if (fmt[i] == 'u')
		ft_print_unsigned_dec(args, pd);
	else if (fmt[i] == 'x')
		ft_print_u_hex(args, pd, false);
	else if (fmt[i] == 'X')
		ft_print_u_hex(args, pd, true);
	else if (fmt[i] == '%')
	{
		pd->total_printed += write(pd->fd, &"%", 1);
		reset_print_data(pd);
	}
	i++;
	return (i);
}

size_t	parse_width_precision(const char *fmt, t_p_data *pd, size_t i)
{
	while (ft_isdigit(fmt[i]))
	{
		pd->width *= 10;
		pd->width += fmt[i] - '0';
		i++;
	}
	if (fmt[i] == '.')
	{
		pd->has_dot = true;
		pd->zero_padding = false;
		i++;
		while (ft_isdigit(fmt[i]))
		{
			pd->precision *= 10;
			pd->precision += fmt[i] - '0';
			i++;
		}
	}
	return (i);
}

size_t	evaluate_flags(const char *fmt, t_p_data *pd, size_t i)
{
	while (1)
	{
		if (fmt[i] == '+')
			pd->plus_sign = true;
		else if (fmt[i] == ' ')
			pd->space = true;
		else if (fmt[i] == '0')
			pd->zero_padding = true;
		else if (fmt[i] == '-')
			pd->dash = true;
		else if (fmt[i] == '#')
			pd->pound = true;
		else
			break ;
		i++;
	}
	return (i);
}
