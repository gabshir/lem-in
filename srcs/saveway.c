/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   saveway.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabshire <gabshire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 14:46:29 by gabshire          #+#    #+#             */
/*   Updated: 2019/05/15 14:48:35 by gabshire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	ft_blok(t_list **links, t_room *test)
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

static int	ft_cheak(t_list *links, int gl, int f)
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

static void	ft_saveup(t_room *read, t_list **waynow, t_room **pred, int *d)
{
	read->isp = 1;
	ft_lstadd(waynow, ft_lstnew_ptr(read));
	ft_blok(&read->links, *pred);
	*pred = read;
	d[0]--;
}

void	ft_saveway(t_room *end, t_list **way, int f, int d)
{
	t_room	*read;
	t_list	*links;
	t_room *pred;
	t_list *waynow;

	links = end->links;
	pred = end;
	waynow = NULL;
	ft_lstadd(&waynow, ft_lstnew_ptr(end));
	while (links)
	{
		read = links->content;
		if (read->gl == d - 1 && ft_cheak(read->links, d, f) == 0)
		{
			ft_saveup(read, &waynow, &pred, &d);
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