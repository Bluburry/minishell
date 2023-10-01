/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 19:33:22 by tpinto-e          #+#    #+#             */
/*   Updated: 2022/12/01 19:33:23 by tpinto-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*mix;
	size_t	length;

	if (!s || !f)
		return (NULL);
	length = ft_strlen(s);
	mix = (char *) malloc((length + 1) * sizeof(char));
	if (!mix)
		return (NULL);
	mix[length] = 0;
	while (length--)
		mix[length] = f(length, s[length]);
	return (mix);
}
