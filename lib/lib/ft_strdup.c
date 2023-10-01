/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 19:32:29 by tpinto-e          #+#    #+#             */
/*   Updated: 2022/12/01 19:32:30 by tpinto-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strdup(const char *s)
{
	char	*t;

	t = (char *) malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!t)
		return (NULL);
	ft_strlcpy(t, s, ft_strlen(s) + 1);
	return (t);
}
