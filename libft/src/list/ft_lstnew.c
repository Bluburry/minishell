/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: remarque <remarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 17:12:31 by remarque          #+#    #+#             */
/*   Updated: 2023/04/17 19:53:23 by remarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*list;

	list = malloc(sizeof(t_list));
	if (!list)
		return (0);
	list->content = content;
	list->next = 0;
	return (list);
}

/*
#include <stdio.h>

int	main(void)
{
	t_list	*list;
	int		x;

	x = 20;
	list = ft_lstnew(&x);
	printf("%d should be 20\n", *(int *)(list->content));
}
// cc ft_lstnew.c
*/