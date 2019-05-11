/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillem- <jwillem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 17:03:40 by jwillem-          #+#    #+#             */
/*   Updated: 2019/05/11 09:52:57 by gabshire         ###   ########.fr       */
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
	way->content_size = 0;
}

int 	ft_cheak(t_list *links, int gl, int f)
{
	t_room *read;

	if (f == 1)
		return (0);
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
	t_list	*temp;

	temp = *links;
	while (temp->next)
		temp = temp->next;
	temp->content_size = i;
}

void	freeway(t_list **way)
{
	t_list *rfree;
	t_list *temp;
	t_list *freenow;

	temp = *way;
	while (temp)
	{
		rfree = temp->content;
		while (rfree)
		{
			freenow = rfree->content;
			ft_lstdel((t_list **) &freenow, NULL);
			rfree = rfree->next;
		}
		temp = temp->next;
	}
	free(*way);
	*way = NULL;
}

static void	ft_saveway(t_room *end, t_list **way, int f)
{
	t_room	*read;
	int 	d;
	t_list	*links;
	t_room *pred;
	t_list *waynow;

	links = end->links;
	pred = end;
	end->isp = 1;
	d = end->gl;
	waynow = NULL;
	ft_lstadd(&waynow, ft_lstnew_ptr(end));
	while (links)
	{
		read = links->content;
		if (read->gl == d - 1 && ft_cheak(read->links, d, f) == 0)
		{
			read->isp = 1;
			ft_lstadd(&waynow, ft_lstnew_ptr(read));
			d--;
			ft_blok(&read->links, pred);
			pred = read;
			links = read->links;
			if (d == 0)
			{
				ft_lstpush(way, ft_lstnew_ptr(waynow));
				break;
			}
		}
		else
			links = links->next;
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

static void restisp(t_list **way)
{
	t_list *temp;
	t_list *combway;
	t_list *links;
	t_room *read;

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

static int path_analysis(t_list **combo)
{
	t_list *last_combo;
	t_list *read_combo;
	t_list *way;
	t_room *readt;
	t_room *reads;
	t_list *links;
	t_room *temp;
	int f;

	last_combo = *combo;
	f = 0;
	while(last_combo->next)
		last_combo = last_combo->next; // ищем последнюю комнату комбинаций
	read_combo = last_combo->content; // получаем список комбинаций
	while (read_combo)
	{
		way = read_combo->content; //  переходим к конкретной комбинации
		while (way->next)
		{
			readt = way->content; // текущий элемент
			reads = way->next->content; // следующий
			links = reads->links;
			while (links) // ищем текущей элемент
			{
				temp = links->content;
				if (readt->n == temp->n && links->content_size == 8) // нашли совпададение но оно не блокированно
					break ;
				else if (readt->n == temp->n)
				{
					ft_freedown(&readt->links, reads->n);
					ft_freedown(&reads->links, readt->n);
					f = 1;
					//return (1);
					links = links->next;
				}
				else
					links = links->next;
			}
			way = way->next;
		}
		read_combo = read_combo->next;
	}
	return (f);
}

void	restornap(t_list **way)
{
	t_list *lastcomb;
	t_list *linkcombo;
	t_list *waynow;
	t_room *read;

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

void	way(t_map *map, int l)
{
	int i;
	t_list *combnow;

	combnow = NULL;
	i = 0;
	while (shirina(map) == 1)
	{
		ft_saveway(&map->end, &combnow, 0);
		restorroom(map);
	}
	ft_lstpush(&map->way, ft_lstnew_ptr(combnow));
	ft_konnekt(&map->way, l);
	combnow = NULL;
	restisp(&map->way);
	restorroom(map);
	while (shirinablok(map) == 1 && i == 0)
	{
		ft_saveway(&map->end, &combnow, 1);
		restorroom(map);
		i = path_analysis(&map->way);
	}
	ft_lstpush(&map->cut, ft_lstnew_ptr(combnow));
	restisp(&map->cut);
	restornap(&map->way);
	restornap(&map->cut);
	freeway(&map->cut);
	restorroom(map);
	if (i == 1)
	{
		l = l + 1;
		way(map, l);
	}
}