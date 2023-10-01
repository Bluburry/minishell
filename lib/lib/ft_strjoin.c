/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 20:02:33 by tpinto-e          #+#    #+#             */
/*   Updated: 2022/12/01 20:02:34 by tpinto-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*string;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	i = ft_strlen(s1);
	j = ft_strlen(s2);
	string = (char *) malloc((i + j + 1) * sizeof(char));
	if (!string)
		return (NULL);
	ft_memmove(string, s1, i);
	ft_memmove(string + i, s2, j + 1);
	string[i + j] = 0;
	return (string);
}
