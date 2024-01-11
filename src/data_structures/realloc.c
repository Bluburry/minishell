/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-e <tpinto-e@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 20:42:18 by tpinto-e          #+#    #+#             */
/*   Updated: 2024/01/11 20:42:19 by tpinto-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// creates a new resource of size size, copies the contents of a ptr 
// of size ptrsize into it and returns the new resource while freeing ptr
// size always needs to be bigger than ptrsize
void	*ft_reallocation(void *ptr, size_t ptrsize, size_t size)
{
	char		*temp;
	uint32_t	i;

	if (ptr == NULL)
		return (malloc(size));
	if (size == 0)
		return (free(ptr), NULL);
	temp = malloc(size);
	if (temp == NULL)
		return (NULL);
	i = 0;
	while (i < ptrsize)
	{
		temp[i] = ((char *)ptr)[i];
		i++;
	}
	return (free(ptr), temp);
}
