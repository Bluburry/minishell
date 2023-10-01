/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 19:31:32 by tpinto-e          #+#    #+#             */
/*   Updated: 2022/12/01 21:35:29 by tpinto-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	void	*ptr;

	ptr = dest;
	if (!dest && !src)
		return (NULL);
	while (n--)
	{
		*(char *)dest++ = *(char *)src++;
	}
	return (ptr);
}
