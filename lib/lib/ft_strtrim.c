/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 19:33:51 by tpinto-e          #+#    #+#             */
/*   Updated: 2022/12/01 21:56:25 by tpinto-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*string;
	int		end;

	if (!s1 || !set)
		return (NULL);
	while (!!ft_strchr(set, *s1) && *s1)
		s1++;
	if (!*s1)
	{
		string = (char *) malloc(1 * sizeof(char));
		string[0] = 0;
	}
	else
	{
		end = (int) ft_strlen(s1) - 1;
		while (!!ft_strchr(set, s1[end]) && s1[end])
			end--;
		string = (char *) malloc((end + 2) * sizeof(char));
		if (!string)
			return (NULL);
		ft_memcpy(string, s1, end + 1);
		string[end + 1] = 0;
	}
	return (string);
}
