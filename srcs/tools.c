/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillem- <jwillem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 04:44:02 by jwillem-          #+#    #+#             */
/*   Updated: 2019/05/12 21:03:28 by jwillem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

// float	connectivity(t_map *map)
// {
// 	int		i;
// 	int		edges;
	
// 	i = -1;
// 	edges = 0;
// 	while (ROOMS[++i])
// 		edges += ft_lstlen(ROOMS[i]->links);
// 	edges /= 2;
// 	ft_printf("\nEdges = %d\nRooms = %d\n", edges, ROOM_Q);
// 	return ((float)edges / (float)ROOM_Q);
// }

int		check_existing_links(t_list *links, char *r_name)
{
	t_list	*ptr;

	ptr = links;
	while (ptr)
	{
		if (!(ft_strcmp(((t_room*)ptr->content)->name, r_name)))
			return (1);
		ptr = ptr->next;
	}
	return (0);
}

int path_analysis(t_list **combo)
{
	t_list *last_combo;
	t_list *read_combo;
	t_list *way;
	t_room *readt;
	t_room *reads;
	t_list *links;
	t_room *temp;
	int f;

	if (*combo == NULL)
		return (0);
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
					links = links->next;
					ft_freedown(&readt->links, reads->n);
					ft_freedown(&reads->links, readt->n);
					f = 1;
					//return (1);
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
	t_list *rfreen;
	t_list *temp;
	t_list *tempn;
	t_list *freenow;

	if (*way == NULL)
		return ;
	temp = *way;
	while (temp)
	{
		rfree = temp->content;
		while (rfree)
		{
			freenow = rfree->content;
			ft_lstdel((t_list **) &freenow, NULL);
			rfreen = rfree->next;
			free(rfree);
			rfree = rfreen;
		}
		tempn = temp->next;
		free(temp);
		temp = NULL;
		temp = tempn;
	}
	*way = temp;
}

void	ft_saveway(t_room *end, t_list **way, int f)
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
