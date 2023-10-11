/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: remarque <remarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 17:12:37 by remarque          #+#    #+#             */
/*   Updated: 2023/04/17 19:53:23 by remarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

/*
#include <stdio.h>

int	main(void)
{
	t_list	*list;
	t_list	*list2;
	int		x;
	int		y;

	x = 20;
	y = 5;
	list = malloc(sizeof(t_list));
	list->next = malloc(sizeof(t_list));
	list->next->next = 0;
	list->content = &x;
	list->next->content = &y;
	printf("%d should be 20\n", *(int *)(list->content));
	printf("%d should be 5\n", *(int *)(list->next->content));
	list2 = ft_lstlast(list);
	printf("%d should be 5\n", *(int *)(list2->content));
}
// cc ft_lstlast.c
*/