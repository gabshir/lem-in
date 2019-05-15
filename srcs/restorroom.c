/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   restorroom.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabshire <gabshire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 20:06:46 by gabshire          #+#    #+#             */
/*   Updated: 2019/05/15 13:37:08 by gabshire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void restisp(t_list **way)
{
	t_list *temp;
	t_list *combway;
	t_list *links;
	t_room *read;

	if (*way == NULL)
		return ;
	temp = *way;
	while (temp->next)
		temp = temp->next;
	combway = temp->content;
	while (combway)
	{
		links = combway->content;
		while (links)
		{
			read = links->content;
			read->isp = 0;
			read->f = 0;
			links = links->next;
		}
		combway = combway->next;
	}
}

void	ft_restor(t_list **links)
{
	t_list	*temp;

	temp = *links;
	while (temp)
	{
		temp->content_size = 8;
		temp = temp->next;
	}
}

void	restornap(t_list **way)
{
	t_list *lastcomb;
	t_list *linkcombo;
	t_list *waynow;
	t_room *read;

	if (*way == NULL)
		return ;
	lastcomb = *way;
	while(lastcomb->next)
		lastcomb = lastcomb->next;
	linkcombo = lastcomb->content;
	while (linkcombo)
	{
		waynow = linkcombo->content;
		while (waynow)
		{
			read = waynow->content;
			ft_restor(&read->links);
			waynow = waynow->next;
		}
		linkcombo = linkcombo->next;
	}
}

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