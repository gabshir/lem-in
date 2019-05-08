/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glubina.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabshire <gabshire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 15:47:25 by gabshire          #+#    #+#             */
/*   Updated: 2019/05/07 17:05:17 by gabshire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	ft_listaddglubina(t_list **up_list, t_list *new)
{
	t_list *temp;
	t_list *temp2;
//	t_room	*readn;
//	t_room	*readu;

	if (new == NULL)
		return ;
//	readn = new->content;
	if (up_list[0] == NULL)
		*up_list = new;
	else
	{
		temp = *up_list;
		temp2 = temp;
		while (temp2->next)
		{
//			readu = temp2->content;
//			if (readn->n == readu->n)
//				return ;
			temp2 = temp2->next;
		}
		temp2->next = new;
	}
}

static void	ft_uplistglubina(t_room *room, t_list **up_list)
{
	t_room *read;
	t_list *temp;

	read = NULL;
	temp = room->links;
	while (temp)
	{
		read = temp->content;
		if (read->f == 0 && temp->content_size == 8)
			ft_listaddglubina(up_list, ft_lstnew_ptr(read));
		temp = temp->next;
	}
}

int	glubina(t_map *map)
{
	t_room *read;
	t_list *up_list;
	t_list *copy;
	t_list *obr;
	int		gl;

	gl = 1;
	up_list = NULL;
	obr = map->start.links;
	copy = obr;
	map->rooms[0]->gl = 0;
	map->rooms[0]->f = 1;
	while (copy)
	{
		if (copy->content_size == 8)
		{
			read = copy->content;
			read->f = 1;
	//		ft_printf("room %s\n", read->name);
			if (read->gl == -1)
				read->gl = gl;
			if (read->n != map->room_q - 1)
				ft_uplistglubina(read, &up_list);
			else
				return (1);
		}
		copy = copy->next;
		if (copy == NULL)
		{
	//		ft_printf("***************\n");
			copy = up_list;
			gl++;
			up_list = NULL;
		}
	}
	return (0);
}