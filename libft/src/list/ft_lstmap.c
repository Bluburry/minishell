/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: remarque <remarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 17:12:34 by remarque          #+#    #+#             */
/*   Updated: 2023/04/17 19:53:23 by remarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static inline t_list	*helper(t_list *lst, t_list *list, void *(*f)(void *),
	void (*del)(void *))
{
	t_list	*temp_l;
	t_list	*first_node;

	first_node = list;
	while (lst)
	{
		temp_l = malloc(sizeof(t_list));
		if (!temp_l)
		{
			ft_lstclear(&first_node, del);
			return (0);
		}
		temp_l->content = f(lst->content);
		temp_l->next = 0;
		list->next = temp_l;
		list = temp_l;
		lst = lst->next;
	}
	return (first_node);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*list;

	if (!lst || !f || !del)
		return (0);
	list = malloc(sizeof(t_list));
	if (!list)
		return (0);
	list->content = f(lst->content);
	list->next = 0;
	lst = lst->next;
	return (helper(lst, list, f, del));
}

/*
#include <stdio.h>

void	*f(void *c)
{
	int	*d;

	d = malloc(sizeof(int));
	*d = (*(int *)c + 2);
	return ((void *)d);
}

void	del(void *c)
{
	free(c);
}

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
	list2 = ft_lstmap(list, f, del);
	printf("%d should be 22\n", *(int *)(list2->content));
	printf("%d should be 7\n", *(int *)(list2->next->content));
}
// cc ft_lstmap.c ft_lstclear.c
*/