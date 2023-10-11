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

static int	ft_puthex_fd(unsigned long n, int fd, bool is_upper)
{
	int	total_printed;

	total_printed = 0;
	if (n >= 16)
	{
		total_printed += ft_puthex_fd(n / 16, fd, is_upper);
		total_printed += ft_puthex_fd(n % 16, fd, is_upper);
	}
	else
	{
		if (is_upper == false)
			total_printed += write(fd, &"0123456789abcdef"[n], 1);
		else
			total_printed += write(fd, &"0123456789ABCDEF"[n], 1);
	}
	return (total_printed);
}

static inline void
	print_padding(t_p_data *pd, bool pad_right, unsigned int digits,
		bool has_pound)
{
	int	padding;

	if (pd->precision > digits)
		digits = pd->precision;
	padding = pd->width - digits;
	if (has_pound)
		padding -= 2;
	if (has_pound && !pd->is_upper && !pad_right && pd->zero_padding)
		pd->total_printed += write(pd->fd, &"0x", 2);
	if (has_pound && pd->is_upper && !pad_right && pd->zero_padding)
		pd->total_printed += write(pd->fd, &"0X", 2);
	while (padding > 0 && pd->dash == pad_right)
	{
		if (pd->zero_padding == true && pd->dash == false)
			pd->total_printed += write(pd->fd, &"0", 1);
		else
			pd->total_printed += write(pd->fd, &" ", 1);
		padding--;
	}
}

static inline unsigned int	count_digits(size_t x)
{
	unsigned int	digits;

	digits = 1;
	while (x / 16 > 0)
	{
		digits++;
		x = x / 16;
	}
	return (digits);
}

void	ft_print_pointer(va_list args, t_p_data *pd)
{
	size_t	ptr;
	int		padding;
	int		digits;

	ptr = va_arg(args, size_t);
	if (ptr == 0)
		digits = 5;
	else
		digits = count_digits(ptr) + 2;
	padding = pd->width - digits ;
	while (padding-- > 0 && pd->dash == false)
		pd->total_printed += write(pd->fd, &" ", 1);
	if (ptr == 0)
		pd->total_printed += write(pd->fd, &"(nil)", 5);
	else
	{
		pd->total_printed += write(pd->fd, &"0x", 2);
		pd->total_printed += ft_puthex_fd(ptr, pd->fd, false);
	}
	padding = pd->width - digits;
	while (padding-- > 0 && pd->dash == true)
		pd->total_printed += write(pd->fd, &" ", 1);
	reset_print_data(pd);
}

void	ft_print_u_hex(va_list args, t_p_data *pd, bool is_upper)
{
	unsigned int	hex;
	unsigned int	digits;
	unsigned int	temp_precision;

	hex = va_arg(args, unsigned int);
	pd->is_upper = is_upper;
	digits = count_digits(hex);
	if (hex == 0 && pd->has_dot)
		digits = 0;
	print_padding(pd, false, digits, pd->pound && hex > 0);
	if (pd->pound && !is_upper && hex > 0 && !pd->zero_padding)
		pd->total_printed += write(pd->fd, &"0x", 2);
	if (pd->pound && is_upper && hex > 0 && !pd->zero_padding)
		pd->total_printed += write(pd->fd, &"0X", 2);
	temp_precision = pd->precision;
	while (temp_precision > digits)
	{
		pd->total_printed += write(pd->fd, &"0", 1);
		temp_precision--;
	}
	if (digits != 0)
		pd->total_printed += ft_puthex_fd(hex, pd->fd, is_upper);
	print_padding(pd, true, digits, pd->pound && hex > 0);
	reset_print_data(pd);
}
