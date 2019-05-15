/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillem- <jwillem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 04:44:02 by jwillem-          #+#    #+#             */
/*   Updated: 2019/05/15 14:52:43 by gabshire         ###   ########.fr       */
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

/*
 	bfs && blokway
 */
t_list	*deque(t_list *que)
{
	t_list	*ptr;

	ptr = que->next;
	free(que);
	que = NULL;
	return (ptr);
}

int	finishfree(t_list **obr, t_list **up_list)
{
	ft_lstdel(obr, NULL);
	ft_lstdel(up_list, NULL);
	return (1);
}

t_list *fiststart(t_list *start)
{
	t_list *temp;

	temp = NULL;
	while (start)
	{
		if (start->content_size == 8)
			ft_lstpush(&temp, ft_lstnew_ptr(start->content));
		start = start->next;
	}
	return (temp);
}

void up_gl(t_list **obr, t_list **up_list, int *gl)
{
	if (*obr == NULL)
	{
		*obr = *up_list;
		gl[0]++;
		*up_list = NULL;
	}
}