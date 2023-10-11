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

static inline long	count_digits(long n, t_p_data *pd, unsigned int *digits)
{
	long			x;

	*digits = 1;
	if (n < 0)
	{
		n *= -1;
		pd->is_negative = true;
	}
	x = n;
	while (x / 10 > 0)
	{
		(*digits)++;
		x = x / 10;
	}
	if (n == 0 && pd->has_dot)
		*digits = 0;
	return (n);
}

static inline void
	print_padding(t_p_data *pd, bool pad_right, size_t digits)
{
	int		padding;
	bool	has_sign;

	has_sign = false;
	if ((pd->is_negative || pd->plus_sign || pd->space) && !pd->is_uint)
		has_sign = true;
	if (pd->is_negative && pd->zero_padding && !pd->is_uint && !pad_right)
		pd->total_printed += write(pd->fd, &"-", 1);
	else if (pd->plus_sign && pd->zero_padding && !pd->is_uint && !pad_right)
		pd->total_printed += write(pd->fd, &"+", 1);
	else if (pd->space && pd->zero_padding && !pd->is_uint && !pad_right)
		pd->total_printed += write(pd->fd, &" ", 1);
	if (pd->precision > digits)
		digits = pd->precision;
	padding = pd->width - has_sign - digits;
	while (padding > 0 && pd->dash == pad_right)
	{
		if (pd->zero_padding == true && pd->dash == false)
			pd->total_printed += write(pd->fd, &"0", 1);
		else
			pd->total_printed += write(pd->fd, &" ", 1);
		padding--;
	}
}

int	ft_putdec_fd(long n, int fd)
{
	int	total_printed;

	total_printed = 0;
	if (n >= 10)
	{
		total_printed += ft_putdec_fd(n / 10, fd);
		total_printed += ft_putdec_fd(n % 10, fd);
	}
	else
		total_printed += write(fd, &"0123456789"[n], 1);
	return (total_printed);
}

void	ft_print_signed_dec(va_list args, t_p_data *pd)
{
	long			n;
	unsigned int	digits;
	unsigned int	temp_precision;

	n = (long)va_arg(args, int);
	n = count_digits(n, pd, &digits);
	print_padding(pd, false, digits);
	if (pd->is_negative && !pd->zero_padding)
		pd->total_printed += write(pd->fd, &"-", 1);
	else if (pd->plus_sign && !pd->zero_padding)
		pd->total_printed += write(pd->fd, &"+", 1);
	else if (pd->space && !pd->zero_padding)
		pd->total_printed += write(pd->fd, &" ", 1);
	temp_precision = pd->precision;
	while (temp_precision > digits)
	{
		pd->total_printed += write(pd->fd, &"0", 1);
		temp_precision--;
	}
	if (digits != 0)
		pd->total_printed += ft_putdec_fd(n, pd->fd);
	print_padding(pd, true, digits);
	reset_print_data(pd);
}

void	ft_print_unsigned_dec(va_list args, t_p_data *pd)
{
	unsigned int	n;
	unsigned int	digits;
	unsigned int	temp_precision;

	n = va_arg(args, unsigned int);
	pd->is_uint = true;
	n = (unsigned int)count_digits(n, pd, &digits);
	print_padding(pd, false, digits);
	temp_precision = pd->precision;
	while (temp_precision > digits)
	{
		pd->total_printed += write(pd->fd, &"0", 1);
		temp_precision--;
	}
	if (digits != 0)
		pd->total_printed += ft_putdec_fd(n, pd->fd);
	print_padding(pd, true, digits);
	reset_print_data(pd);
}
