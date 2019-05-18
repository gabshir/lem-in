/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillem- <jwillem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 03:38:24 by jwillem-          #+#    #+#             */
/*   Updated: 2019/05/19 02:07:24 by jwillem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	map_initialisation(t_map *map)
{
	map->ants = 0;
	map->start.name = NULL;
	map->end.name = NULL;
	map->room_q = 0;
	map->rooms = NULL;
	map->way = NULL;
	map->cut = NULL;
}

static void	free_comb(t_map *map)
{
	int	i;

	i = -1;
	while (++i < C_QUANT)
		free(C_WAY[i].rooms);
	free(C_WAY);
}

void	ft_globalfree(t_map *map)
{
	size_t  i;

	i = 1;
	ft_lstdel(&map->start.links, NULL);
	free(map->start.name);
	map->rooms[0] = NULL;
	map->start.name = NULL;
	ft_lstdel(&map->end.links, NULL);
	free(map->end.name);
	map->end.name = NULL;
	while (i < map->room_q - 1)
	{
		ft_lstdel(&map->rooms[i]->links, NULL);
		free(map->rooms[i]->name);
		map->rooms[i]->name = NULL;
		free(map->rooms[i]);
		map->rooms[i] = NULL;
		i++;
	}
	free_comb(map);
	free(map->rooms);
	map->rooms = NULL;
	freeway(&map->way);
}

int		main(/*int ac, char **av*/void)
{
	t_map	map;

	map_initialisation(&map);
	get_map_info(&map, 1);
	if (map.rooms == NULL)
	{
		ft_printf("ERROR. FREE MAP\n");
		exit(1);
	}
	way(&map, 0);
	if (map.way == NULL)
	{
		ft_printf("ERROR. No links thitf start - finish\n");
		ft_globalfree(&map);
		exit(1);
	}
	ant_flow(&map);
	// if (ac == 2 && !ft_strcmp(av[1], "-v"))
	// 	visualization(&map);
	ft_globalfree(&map);
	return (0);
}
