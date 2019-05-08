/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   val_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillem- <jwillem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 14:14:38 by jwillem-          #+#    #+#             */
/*   Updated: 2019/04/05 12:06:09 by gabshire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_room	**sorted_rooms_ptr_array(t_map *map, t_list **room_list)
{
	t_room	**rooms;
	t_list	*ptr;

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

void	check_name_duplicates(t_map *map)
{
	int	i;
	int	j;
	int	duplicates;

	i = 0;
	j = 1;
	duplicates = 0;
	while (i < map->room_q)
	{
		while (j < map->room_q)
		{
			if (!ft_strcmp(map->rooms[i]->name, map->rooms[i + j]->name))
			{
				duplicates++;
				ft_printf(ER "Found dupl. for room %s\n", map->rooms[i]->name);
			}
			j++;
		}
		i++;
	}
	map->error += duplicates;
	if (duplicates)
	{
		ft_printf("\nBe careful, you've made %d mistakes in map.\n", map->error);
		exit(1);
	}
}

void	organize_links(t_map *map, char *line)
{
	char	**split;

	split = ft_strsplit(line, '-');
	if (split[2])
	{
		ft_printf(ER "You've entered excess link info: %s.\n", split[2]);
		map->error++;
		freesplit(split);
		return ;
	}
	create_link(map, split[0], split[1]);
	
	freesplit(split);
}

t_room	*find_room_by_name(t_map *map, char *r_name, int first, int last)
{
	t_room	*ptr;
	int		i;

	if (first > last)
	{
		ft_printf(ER "Incorrect room name in link.\n");
		map->error++;
		return (NULL);
	}
	i = first + (last - first) / 2;
	if (ft_strcmp(ROOMS[i]->name, r_name) > 0)
		ptr = find_room_by_name(map, r_name, first, i - 1);
	else if (ft_strcmp(ROOMS[i]->name, r_name) < 0)
		ptr = find_room_by_name(map, r_name, i + 1, last);
	else
	{
		ptr = ROOMS[i];
		ptr->links = ROOMS[i]->links;
	}
	return (ptr);
}

void	create_link(t_map *map, char *name_fst, char *name_snd)
{
	t_room	*first;
	t_room	*second;

	first = NULL;
	second = NULL;
	if (!ft_strcmp(ROOMS[0]->name, name_fst))
		first = ROOMS[0];
	else if (!ft_strcmp(ROOMS[ROOM_Q - 1]->name, name_fst))
		first = ROOMS[ROOM_Q - 1];
	else
		first = find_room_by_name(map, name_fst, 1, ROOM_Q - 1);
	if (!ft_strcmp(ROOMS[0]->name, name_snd))
		second = ROOMS[0];	
	else if (!ft_strcmp(ROOMS[ROOM_Q - 1]->name, name_snd))
		second = ROOMS[ROOM_Q - 1];
	else
		second = find_room_by_name(map, name_snd, 1, ROOM_Q - 1);
	if (first && second)
	{
		if (!check_existing_links(first->links, second->name))
			ft_lstadd(&first->links, ft_lstnew_ptr((t_room*)second));
		if (!check_existing_links(second->links, first->name))
			ft_lstadd(&second->links, ft_lstnew_ptr((t_room*)first));
	}
	else
	{
		if (!first)
		{
			ft_printf(ER "Room %s is not found.\n", name_fst);
			map->error++;
		}
		if (!second)
		{
			ft_printf(ER "Room %s is not found.\n", name_snd);
			map->error++;
		}
	}
}
