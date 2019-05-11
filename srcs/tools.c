/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillem- <jwillem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 04:44:02 by jwillem-          #+#    #+#             */
/*   Updated: 2019/05/11 21:00:59 by jwillem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

float	connectivity(t_map *map)
{
	int		i;
	int		edges;
	
	i = -1;
	edges = 0;
	while (ROOMS[++i])
		edges += ft_lstlen(ROOMS[i]->links);
	edges /= 2;
	ft_printf("\nEdges = %d\nRooms = %d\n", edges, ROOM_Q);
	return ((float)edges / (float)ROOM_Q);
}

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
