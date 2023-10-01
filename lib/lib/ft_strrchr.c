/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 19:33:47 by tpinto-e          #+#    #+#             */
/*   Updated: 2022/12/06 19:40:50 by tpinto-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*ptr;

	ptr = (char *) s;
	while (*s)
		s++;
	while (s != ptr)
	{
		if (*(unsigned char *) s == (unsigned char) c)
			return ((char *) s);
		s--;
	}
	if (*(unsigned char *) s == (unsigned char) c)
		return ((char *) s);
	return (NULL);
}
