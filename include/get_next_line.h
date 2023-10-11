/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: remarque < remarque@student.42porto.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 19:16:00 by remarque          #+#    #+#             */
/*   Updated: 2023/10/04 16:39:44 by remarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "libft.h"
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 50000
# endif
# ifndef MAX_N_BUFFERS
#  define MAX_N_BUFFERS USHRT_MAX
# endif

size_t	ft_searcher(const char *str, int c);

#endif