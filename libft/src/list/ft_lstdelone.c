/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: remarque <remarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 17:12:42 by remarque          #+#    #+#             */
/*   Updated: 2023/04/17 19:53:23 by remarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (!lst || !del)
		return ;
	del(lst->content);
	free(lst);
	lst = 0;
}

/*
#include <stdio.h>

void	del(void *c)
{
	return ;
}

int	main(void)
{
	t_list	*list;
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
	ft_lstdelone(list->next, del);
	printf("%p should be an adress\n", list->next);
	printf("%p should be (nil)\n", list->next->content);
}
// cc ft_lstdelone.c
*/