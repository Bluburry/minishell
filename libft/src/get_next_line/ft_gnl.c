/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gnl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: remarque < remarque@student.42porto.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 22:54:08 by remarque          #+#    #+#             */
/*   Updated: 2023/10/04 16:36:54 by remarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#define CAPACITY 1024

static inline void	push_char(char c, t_str *str)
{
	char	*temp;
	int		i;

	if (str->size + 1 >= str->capacity)
	{
		temp = ft_calloc(str->capacity * 2, sizeof(char));
		if (!temp)
			return ;
		i = -1;
		while (++i < (int)str->size)
			temp[i] = str->str[i];
		free(str->str);
		str->str = temp;
		str->capacity *= 2;
	}
	str->str[str->size] = c;
	str->size++;
}

char	*ft_gnl(int fd)
{
	char	c;
	t_str	line;
	int		res;

	line.str = ft_calloc(CAPACITY, sizeof(char));
	if (!line.str)
		return (NULL);
	line.capacity = CAPACITY;
	line.size = 0;
	while (1)
	{
		res = read(fd, &c, 1);
		if (res <= 0)
			break ;
		push_char(c, &line);
		if (c == '\n')
			break ;
	}
	if (line.size == 0 || res == -1)
	{
		free(line.str);
		return (NULL);
	}
	return (line.str);
}
