/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillem- <jwillem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 17:03:40 by jwillem-          #+#    #+#             */
/*   Updated: 2019/05/08 13:54:27 by gabshire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	ft_blok(t_list **links, t_room *test)
{
	t_list	*way;
	t_room	*read;

	way = *links;
	read = way->content;
	while (read->n != test->n)
	{
		way = way->next;
		read = way->content;
	}
//	ft_printf("chto %s\n", read->name);
	way->content_size = 0;
}

int 	ft_cheak(t_list *links, int gl)
{
	t_room *read;
	while (links)
	{
		read = links->content;
		if (read->gl == gl && links->content_size == 8)
			return (0);
		links = links->next;
	}
	return (1);
}

void	ft_konnekt(t_list **links, size_t i)
{
	{
		t_list	*temp;

		temp = *links;
		while (temp->next)
			temp = temp->next;
		temp->content_size = i;
	}
}
/*
int otsew(t_list *way, t_list *new, size_t i) // way - пути, new - добавляемые пути, в какой группе комнат искать
{
	t_list *temp; // распоковка путей
	t_room *roomw;
	t_room *roomn;
	t_list *pred;

	pred = new->next;
	new = new->next;

	while (way && way->content_size != i)
		way = way->next;
	while (way)
	{
		temp = way->content;
		temp = temp->next;
		roomw = temp->content;
		roomn = new->content;
		while (roomw->n != 0)
		{
			if (roomn == roomw)
				return (1);
			new = new->next;
			roomw = new->content;
		}
		new = pred;
		way = way->next;
	}
	return (0);
}
*/

void	freeway(t_list **way)
{
	t_list *temp;
	t_list *pred;

	temp = *way;
	pred = *way;
	while (temp->next)
	{
		pred = temp;
		temp = temp->next;
	}
	free(temp);
	temp = NULL;
	pred->next = temp;
}
void	ft_printfway(t_room	*end, t_list **way, size_t i)
{
	t_room	*read;
	int 	d;
	t_list	*links;
	t_room *pred;
	t_list *waynow;

	links = end->links;
	pred = end;
//	ft_printf("###############\n");

	end->isp = 1;
	d = end->gl;
	waynow = NULL;
//	ft_listaddglubina(&waynow, ft_lstnew_ptr(end));
	ft_lstpush(&waynow, ft_lstnew_ptr(end));
	while (links)
	{
		read = links->content;
		if (read->gl == d - 1 && ft_cheak(read->links, d) == 0)
		{
			read->isp = 1;
//			ft_listaddglubina(&waynow, ft_lstnew_ptr(read));
			ft_lstpush(&waynow, ft_lstnew_ptr(read));
	//		ft_printf("way = %s\n", read->name);
			d--;
			ft_blok(&read->links, pred);
			pred = read;
			links = read->links;
			if (d == 0)
			{
//				ft_listaddglubina(way, ft_lstnew_ptr(waynow));
				ft_lstpush(way, ft_lstnew_ptr(waynow));
				ft_konnekt(way, i);
				break;
			}
		}
		else
			links = links->next;
	}
//	ft_printf("way = %s\n", read->name);
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

int	ft_freeroom(t_room *room)
{
	int f;
	t_list *links1;
	t_list *links2;
	t_list *links3;
	t_room *read1;
	t_room *read2;
	t_room *read3;

	f = 0;
	links1 = room->links;
	while (links1) // линки текущей комнаты
	{
		if (links1->content_size == 0) // найдена заблокированная комната
		{
			read1 = links1->content;
			links2 = read1->links;
			while (links2) // линки заблокированной комнаты
			{
				if (links2->content_size == 0)
				{
					read2 = links2->content;
					links3 = read2->links;
					while (links3)
					{
						if (links3->content_size == 0)
						{
							read3 = links3->content;
							if (read1->n == read3->n)
							{
								ft_freedown(&read2->links, read3->n);
								ft_freedown(&read3->links, read2->n);
								f = 1;
							}
						}
						links3 = links3->next;
					}
				}
				links2 = links2->next;
			}
		}
		links1 = links1->next;
	}
	return (f);
}

void	way(t_map *map)
{
	int i;
	int k;
	size_t l;

	k = 0;
	l = 0;
	while (k != 0 || glubina(map) != 0)
	{
		i = 0;
		ft_printfway(&map->end, &map->way, l);
		while (map->rooms[i])
		{
			map->rooms[i]->f = 0;
			map->rooms[i]->gl = -1;
			map->rooms[i]->isp = 0;
			k = ft_freeroom(map->rooms[i]) + k;
			i++;
		}
		if (k > 0)
		{
			freeway(&map->way);
			i = 0;
			l++;
		//	ft_printf("!!!!!!!!!!!!!!!!!!!!!\n");
			while (map->rooms[i])
			{
				ft_restor(&map->rooms[i]->links);
				i++;
			}
			k = 0;
		}
	}
}