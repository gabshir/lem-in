/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillem- <jwillem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 03:38:24 by jwillem-          #+#    #+#             */
/*   Updated: 2019/05/15 21:42:09 by jwillem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	map_initialisation(t_map *map)
{
	map->error = 0;
	map->ants = 0;
	map->start.name = NULL;
	map->end.name = NULL;
	map->room_q = 0;
	map->rooms = NULL;
	map->way = NULL;
	map->cut = NULL;
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
	free(map->rooms);
	map->rooms = NULL;
	freeway(&map->way);
}

int		main(int ac, char **av)
{
	t_map	map;
	int		fd;
	// int i;

	ac = 0;
	// i = 0;
	fd = ft_read_file(av[1]);
	if (fd == -1)
		exit(1);
	map_initialisation(&map);
	get_map_info(&map, fd);
	if (map.error)
	{
		ft_printf("\nBe careful, you've made %d mistakes in map.\n", map.error);
		exit(1);
	}
	// ft_printf("########\n");
	// ft_printf("\nConnectivity = %f\n", map.connectivity); // debug
	// visualization(&map);
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
	// ft_printway(map.way); // debug
	ant_flow(&map);
//	visualization(&map);
	ft_globalfree(&map);
	return (0);
}
