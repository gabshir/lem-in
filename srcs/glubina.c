/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glubina.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabshire <gabshire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 15:47:25 by gabshire          #+#    #+#             */
/*   Updated: 2019/05/10 18:54:51 by gabshire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	ft_listaddshirina(t_list **up_list, t_room *read)
{
	t_list *temp;
	t_list *temp2;
	t_room	*readu;

	if (up_list[0] == NULL)
		*up_list = ft_lstnew_ptr(read);
	else
	{
		temp = *up_list;
		temp2 = temp;
		while (temp2->next)
		{
			readu = temp2->content;
			if (read->n == readu->n)
				return;
			temp2 = temp2->next;
		}
		temp2->next = ft_lstnew_ptr(read);
	}
}

static void	ft_uplistshirina(t_room *room, t_list **up_list)
{
	t_room *read;
	t_list *temp;

	temp = room->links;
	while (temp)
	{
		read = NULL;
		read = temp->content;
		if (read->f == 0)
			ft_listaddshirina(up_list, read);
		temp = temp->next;
	}
}

static void incmap(t_map *map)
{
	map->start.gl = 0;
	map->start.f = 1;
	map->end.isp = 0;
	map->end.f = 0;
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

t_list	*deque(t_list *que)
{
	t_list	*ptr;

	ptr = que->next;
	free(que);
	que = NULL;
	return (ptr);
}

int	shirina(t_map *map)
{
	t_room *read;
	t_list *up_list;
	t_list *obr;
	int		gl;

	gl = 1;
	up_list = NULL;
	obr = fiststart(map->start.links);
	incmap(map);
	while (obr)
	{
		read = obr->content;
		if (read->isp == 0 && read->f == 0)
		{
			read->f = 1;
			read->gl = gl;
			if (read->n != map->end.n)
				ft_uplistshirina(read, &up_list);
			else
				{
					ft_lstdel(&obr, NULL);
					ft_lstdel(&up_list, NULL);
					return (1);
				}
		}
		obr = deque(obr);
		if (obr == NULL)
		{
			obr = up_list;
			gl++;
			up_list = NULL;
		}
	}
	return (0);
}