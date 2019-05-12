/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   restorroom.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabshire <gabshire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 20:06:46 by gabshire          #+#    #+#             */
/*   Updated: 2019/05/12 19:03:31 by gabshire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	ft_uplistfree(t_room *room, t_list **up_list)
{
	t_room *read;
	t_list *temp;

	temp = room->links;
	while (temp)
	{
		read = NULL;
		read = temp->content;
		if (read->f == 1)
			ft_lstpush(up_list, ft_lstnew_ptr(read));
		temp = temp->next;
	}
}

void	restorroom(t_map *map)
{
	t_list *obr;
	t_list *up_list;
	t_room *read;

	obr = fiststart(map->start.links);
	up_list = NULL;
	while (obr)
	{
		read = NULL;
		read = obr->content;
		if (read->f == 1)
		{
			read->gl = -1;
			read->f = 0;
			ft_uplistfree(read, &up_list);
		}
		obr = deque(obr);
		if (obr == NULL)
		{
			obr = up_list;
			up_list = NULL;
		}
	}
}