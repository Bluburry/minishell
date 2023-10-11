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

void	evaluate_format_string(va_list args, const char *fmt, t_p_data *pd)
{
	size_t	i;

	i = 0;
	while (fmt[i])
	{
		if (fmt[i] != '%')
		{
			pd->total_printed += write(pd->fd, &fmt[i], 1);
			i++;
		}
		else
		{
			i++;
			i = evaluate_flags(fmt, pd, i);
			i = parse_width_precision(fmt, pd, i);
			i = print_argument(args, fmt, pd, i);
		}
	}
}

int	ft_printf(const char *format, ...)
{
	va_list		args;
	t_p_data	print_data;

	print_data.fd = 1;
	print_data.total_printed = 0;
	reset_print_data(&print_data);
	va_start(args, format);
	evaluate_format_string(args, format, &print_data);
	va_end(args);
	return (print_data.total_printed);
}
