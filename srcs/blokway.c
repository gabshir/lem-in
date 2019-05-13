/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blokway.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabshire <gabshire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 19:40:19 by gabshire          #+#    #+#             */
/*   Updated: 2019/05/13 17:06:16 by gabshire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	ft_uplistshirinablok(t_room *room, t_list **up_list)
{
	t_room *read;
	t_list *temp;

	temp = room->links;
	while (temp)
	{
		read = NULL;
		read = temp->content;
		if (read->f == 0 && temp->content_size == 8)
			ft_listaddshirina(up_list, read);
		temp = temp->next;
	}
}

int shirinablok(t_map *map)
{
	t_list *start;
	t_list *up_list;
	t_room *read;
	int gl;

	gl = 1;
	start = fiststart(map->start.links);
	up_list = NULL;
	while (start)
	{
		read = start->content;
		if (read->f == 0)
		{
			read->f = 1;
			read->gl = gl;
			ft_uplistshirinablok(read, &up_list);
			if (read->n == map->end.n)
				return (finishfree(&start, &up_list));
		}
		start = deque(start);
		up_gl(&start, &up_list, &gl);
	}
	return (0);
}