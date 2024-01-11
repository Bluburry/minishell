/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-e <tpinto-e@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 20:41:44 by tpinto-e          #+#    #+#             */
/*   Updated: 2024/01/11 20:41:45 by tpinto-e         ###   ########.fr       */
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