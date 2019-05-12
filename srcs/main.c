/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillem- <jwillem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 03:38:24 by jwillem-          #+#    #+#             */
/*   Updated: 2019/05/12 21:03:51 by jwillem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "lem_in.h"

void	quantity_of_ants(t_map *map, char *line)
{
	char	*str;

	map->ants = ft_atoi(line);
	str = ft_itoa(map->ants);
	if (ft_strcmp(str, line) || map->ants < 1)
	{
		ft_printf(ER "Incorrect number of ants!");
		map->error++;
	}
	free(str);
}

void	get_map_info(t_map *map, int fd)
{
	char	*line;
	t_list	*room_list;
	t_room	*room;
	e_sort	time_to_sort;
	
	room_list = NULL;
	time_to_sort = not_sorted;
	while (get_next_line(fd, &line) > 0)
	{
		ft_printf("%s\n", line);
		if (map->ants == 0 && map->error == 0)
			quantity_of_ants(map, line);
		else if (!ft_strcmp(line, "##start"))
			start_init(map, line, fd);
		else if (!ft_strcmp(line, "##end"))
			end_init(map, line, fd);
		else if (ft_strchr(line, ' ') && ft_strncmp(line, "#", 1))
		{
			if (time_to_sort == sorted)
			{
				ft_printf(ER "No more rooms after connections have started!\n");
				map->error++;
				continue ;
			}
			room = create_room(map, line);
			if (room)
				ft_lstadd(&room_list, ft_lstnew_ptr(room));
		}
		else if (ft_strchr(line, '-') && ft_strncmp(line, "#", 1))
		{
			if (time_to_sort == not_sorted)
			{
				map->rooms = sorted_rooms_ptr_array(map, &room_list);
				check_name_duplicates(map);
			}
			time_to_sort = sorted;
			organize_links(map, line);
		}
		free(line);
	}
	// map->connectivity = connectivity(map);
}

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
//	free(map->end.name);
	map->end.name = NULL;
	while ((int)i < map->room_q - 1)
	{
		ft_lstdel(&map->rooms[i]->links, NULL);
		free(map->rooms[i]->name);
		map->rooms[i]->name = NULL;
		free(map->rooms[i]);
		map->rooms[i] = NULL;
		i++;
	}
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
	way(&map, 0);
	// ft_printway(map.way); // debug
	ant_flow(&map);
	// visualization(&map);
	ft_globalfree(&map);
	return (0);
}

//Test comment################

