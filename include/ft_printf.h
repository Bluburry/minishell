/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: remarque <remarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 19:16:38 by remarque          #+#    #+#             */
/*   Updated: 2023/04/17 18:14:45 by remarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdarg.h>
# include <stdbool.h>

typedef struct s_print_data
{
	int				fd;
	int				total_printed;
	unsigned int	width;
	unsigned int	precision;
	bool			has_dot;
	bool			pound;
	bool			plus_sign;
	bool			zero_padding;
	bool			dash;
	bool			space;
	bool			is_negative;
	bool			is_uint;
	bool			is_upper;
}	t_p_data;

int		ft_printf(const char *format, ...);

//t_print_data	*new_print_data(void);
void	reset_print_data(t_p_data *pd);

size_t	evaluate_flags(const char *fmt, t_p_data *pd, size_t i);
size_t	print_argument(va_list args, const char *fmt, t_p_data *pd, size_t i);
size_t	parse_width_precision(const char *fmt, t_p_data *pd, size_t i);

void	ft_print_char(va_list args, t_p_data *pd);
void	ft_print_string(va_list args, t_p_data *pd);
void	ft_print_pointer(va_list args, t_p_data *pd);
void	ft_print_signed_dec(va_list args, t_p_data *pd);
void	ft_print_unsigned_dec(va_list args, t_p_data *pd);
void	ft_print_u_hex(va_list args, t_p_data *pd, bool is_upper);

#endif