/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   val_tools2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillem- <jwillem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 17:42:52 by jwillem-          #+#    #+#             */
/*   Updated: 2019/05/19 03:52:17 by gabshire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_room	**sorted_rooms_ptr_array(t_map *map, t_list **room_list)
{
	t_room	**rooms;
	t_list	*ptr;
	int		i;

	if (!(rooms = (t_room**)ft_memalloc(sizeof(t_room*) * (map->room_q + 1))))
	{
		ft_printf(ER "Couldn't allocate memory.\n");
		exit(1);
	}
	rooms[0] = &map->start;
	rooms[map->room_q - 1] = &map->end;
	rooms[map->room_q] = NULL;
	ptr = *room_list;
	while (ptr)
	{
		put_ptr_in_array(map->room_q - 2, rooms, (t_room*)ptr->content);
		ptr = ptr->next;
	}
	i = -1;
	while (rooms[++i])
		rooms[i]->n = i;
	ft_lstdel(room_list, NULL);
	return (rooms);
}

void	put_ptr_in_array(int penultimate, t_room **rooms, t_room *room)
{
	int	i;

	i = 1;
	while (i <= penultimate)
	{
		if (rooms[i])
		{
			if (ft_strcmp(room->name, rooms[i]->name) < 0)
			{
				rooms[i - 1] = room;
				break ;
			}
			else if (ft_strcmp(room->name, rooms[i]->name) >= 0)
				rooms[i - 1] = rooms[i];
		}
		i++;
	}
	if (i == penultimate + 1)
		rooms[penultimate] = room;
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

void	validate_axis(t_room *room, char *splitstr, char axis)
{
	char	*str;
	int		f;

	f = 0;
	(splitstr == NULL) ? f = 1 : 0;
	if (axis == 'X' && f == 0)
	{
		room->x = ft_atoi(splitstr);
		str = ft_itoa(room->x);
	}
	else if (axis == 'Y' && f == 0)
	{
		room->y = ft_atoi(splitstr);
		str = ft_itoa(room->y);
	}
	else
		str = NULL;
	if (f == 1 || ft_strcmp(splitstr, str) || room->x < 0 || room->y < 0)
	{
		ft_printf(ER "Incorrect %c coordinate for room.\n", axis);
		exit(1);
	}
	free(str);
}

int		chec_start_finish(t_map *map, char *line, int print)
{
	if (!ft_strcmp(line, "##start"))
	{
		start_init(map, line, print);
		return (1);
	}
	if (!ft_strcmp(line, "##end"))
	{
		end_init(map, line, print);
		return (1);
	}
	return (0);
}
