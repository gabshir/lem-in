/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillem- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 21:08:30 by jwillem-          #+#    #+#             */
/*   Updated: 2019/04/05 12:06:09 by gabshire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*newlist;
	t_list	*cont;
	t_list	*list;

	if (!lst || !*f)
		return (NULL);
	newlist = NULL;
	cont = f(lst);
	if ((newlist = ft_lstnew(cont->content, cont->content_size)))
	{
		list = newlist;
		lst = lst->next;
		while (lst)
		{
			cont = f(lst);
			if (!(list->next = ft_lstnew(cont->content, cont->content_size)))
				return (NULL);
			list = list->next;
			lst = lst->next;
		}
	}
	return (newlist);
}
