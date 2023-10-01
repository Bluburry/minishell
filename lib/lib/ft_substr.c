/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 19:34:01 by tpinto-e          #+#    #+#             */
/*   Updated: 2022/12/07 14:59:29 by tpinto-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*t;
	int		size;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
	{
		t = (char *) malloc(1 * sizeof(char));
		if (!t)
			return (NULL);
		*t = 0;
		return (t);
	}
	size = len;
	if ((ft_strlen(s) - start) < len)
		size = ft_strlen(s) - start;
	t = (char *) malloc((size + 1) * sizeof(char));
	if (!t)
		return (NULL);
	t[size] = 0;
	while (size--)
		t[size] = s[size + start];
	return (t);
}
