/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   val_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillem- <jwillem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 14:14:38 by jwillem-          #+#    #+#             */
/*   Updated: 2019/05/19 01:39:56 by jwillem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	check_name_duplicates(t_map *map)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 1;
	while (i < map->room_q)
	{
		while (j < map->room_q)
		{
			if (ft_strcmp(map->rooms[i]->name, map->rooms[i + j]->name) == 0)
			{
				ft_printf(ER "Found dupl. for room %s\n", map->rooms[i]->name);
				exit(1);
			}
			j++;
		}
		i++;
	}
}

void	organize_links(t_map *map, char *line)
{
	char	**split;

	split = ft_strsplit(line, '-');
	if (split[2])
	{
		ft_printf(ER "You've entered excess link info: %s.\n", split[2]);
		exit(1);
	}
	if (split[0]== NULL || split[1] == NULL)
	{
		ft_printf("error pipes\n");
		exit(1);
	}
	create_link(map, split[0], split[1]);
	freesplit(split);
}

t_room	*find_room_by_name(t_map *map, char *r_name,
		int first, int last)
{
	t_room	*ptr;
	int		i;

	if (first > last)
	{
		ft_printf(ER "Incorrect room name in link.\n");
		exit(1);
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

static void ft_listadd_links(t_room *first, t_room *second)
{
	if (!check_existing_links(first->links, second->name))
		ft_lstadd(&first->links, ft_lstnew_ptr((t_room*)second));
	if (!check_existing_links(second->links, first->name))
		ft_lstadd(&second->links, ft_lstnew_ptr((t_room*)first));
}

void	create_link(t_map *map, char *name_fst, char *name_snd)
{
	t_room	*first;
	t_room	*second;

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
		ft_listadd_links(first, second);
	else
	{
		if (!first)
			error_create_links(name_fst);
		if (!second)
			error_create_links(name_snd);
	}
}
