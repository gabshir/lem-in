/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   patch_analysis.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabshire <gabshire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 14:38:51 by gabshire          #+#    #+#             */
/*   Updated: 2019/05/15 14:38:51 by gabshire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	linksfree(t_list *links, t_room *readt, t_room *reads, int *f)
{
	t_room *temp;

	while (links)
	{
		temp = links->content;
		if (readt->n == temp->n && links->content_size == 8)
			break ;
		else if (readt->n == temp->n)
		{
			links = links->next;
			ft_freedown(&readt->links, reads->n);
			ft_freedown(&reads->links, readt->n);
			f[0] = 1;
		}
		else
			links = links->next;
	}
}

static void inc_patch_analysis(t_room **readt, t_room **reads, t_list *way, t_list **links)
{
	readt[0] = way->content;
	reads[0] = way->next->content;
	links[0] = reads[0]->links;
}

static t_list *last_combinations(t_list **combo, int *f)
{
	t_list *last_combo;

	f[0] = 0;
	last_combo = *combo;
	while(last_combo->next)
		last_combo = last_combo->next;
	return (last_combo);
}

int path_analysis(t_list **combo)
{
	t_list *last_combo;
	t_list *read_combo;
	t_list *way;
	t_room *readt;
	t_room *reads;
	t_list *links;
	int f;

	if (*combo == NULL)
		return (0);
	last_combo = last_combinations(combo, &f);
	read_combo = last_combo->content;
	while (read_combo)
	{
		way = read_combo->content;
		while (way->next)
		{
			inc_patch_analysis(&readt, &reads, way, &links);
			linksfree(links, readt, reads, &f);
			way = way->next;
		}
		read_combo = read_combo->next;
	}
	return (f);
}