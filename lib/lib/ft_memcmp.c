/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 19:31:25 by tpinto-e          #+#    #+#             */
/*   Updated: 2022/12/01 19:31:26 by tpinto-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	while (n--)
	{
		if (*(unsigned char *)s1 < *(unsigned char *)s2)
			return (-1);
		else if (*(unsigned char *)s1 > *(unsigned char *)s2)
			return (1);
		s1++;
		s2++;
	}
	return (0);
}
