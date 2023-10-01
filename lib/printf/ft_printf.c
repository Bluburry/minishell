/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 15:06:22 by tpinto-e          #+#    #+#             */
/*   Updated: 2023/03/03 18:51:29 by tpinto-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	handler(char c, va_list args)
{
	if (c == '%')
	{
		ft_putchar_fd('%', 1);
		return (1);
	}
	else if (c == 'c')
	{
		ft_putchar_fd(va_arg(args, int), 1);
		return (1);
	}
	else if (c == 's')
		return (ft_print_str(va_arg(args, char *)));
	else if (c == 'p')
		return (ft_print_ptr(va_arg(args, unsigned long)));
	else if (c == 'd' || c == 'i')
		return (ft_print_dec(va_arg(args, int)));
	else if (c == 'u')
		return (ft_print_uns_dec(va_arg(args, unsigned int)));
	else if (c == 'x' || c == 'X')
		return (ft_print_hexa(c, va_arg(args, unsigned int)));
	else
		return (ft_print_str("invalid specifier"));
}

int	ft_printf(const char *str, ...)
{
	va_list	arg_list;
	int		str_i;
	int		args_i;

	if (!str)
		return (ft_print_str("(NULL)"));
	va_start(arg_list, str);
	str_i = 0;
	args_i = 0;
	while (str[str_i])
	{
		if (str[str_i] == '%')
			args_i += handler(str[++str_i], arg_list);
		else
		{
			ft_putchar_fd(str[str_i], 1);
			args_i++;
		}
		str_i++;
	}
	va_end(arg_list);
	return (args_i);
}
