/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_sted.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: remarque < remarque@student.42porto.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 20:50:28 by remarque          #+#    #+#             */
/*   Updated: 2023/10/08 20:50:41 by remarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup_sted(const char *src, int start, int end)
{
	char	*str;
	int		i;

	str = malloc((end - start + 1) * sizeof(char));
	if (!str)
		return (0);
	i = 0;
	while (start < end)
	{
		str[i] = src[start];
		i++;
		start++;
	}
	str[i] = 0;
	return (str);
}
