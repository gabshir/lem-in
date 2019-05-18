/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillem- <jwillem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 04:44:02 by jwillem-          #+#    #+#             */
/*   Updated: 2019/05/17 17:58:53 by jwillem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
**	bfs && blokway
*/

t_list	*deque(t_list *que)
{
	t_list	*ptr;

	ptr = que->next;
	free(que);
	que = NULL;
	return (ptr);
}

int	finishfree(t_list **obr, t_list **up_list)
{
	ft_lstdel(obr, NULL);
	ft_lstdel(up_list, NULL);
	return (1);
}

t_list *fiststart(t_list *start)
{
	t_list *temp;

	temp = NULL;
	while (start)
	{
		if (start->content_size == 8)
			ft_lstpush(&temp, ft_lstnew_ptr(start->content));
		start = start->next;
	}
	return (temp);
}

void up_gl(t_list **obr, t_list **up_list, int *gl)
{
	if (*obr == NULL)
	{
		*obr = *up_list;
		gl[0]++;
		*up_list = NULL;
	}
}