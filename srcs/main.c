/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillem- <jwillem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 03:38:24 by jwillem-          #+#    #+#             */
/*   Updated: 2019/05/08 11:46:30 by gabshire         ###   ########.fr       */
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
	map->short_ways = (links_quantity(&map->start) < links_quantity(&map->end) ? \
		links_quantity(&map->start) : links_quantity(&map->end));
}

void	map_initialisation(t_map *map)
{
	map->error = 0;
	map->ants = 0;
	map->start.name = NULL;
	map->end.name = NULL;
	map->room_q = 0;
	map->rooms = NULL;
	map->p = NULL;
	map->f = /*1*/0;
	map->way = NULL;
}

void	ft_printway(t_list *obway)
{
	t_list	*way;
	t_room *read;
	size_t  proxod;
	int kolway;

	proxod = 1;
	kolway = 0;
	while(obway)
	{
		if (proxod != obway->content_size)
		{
			proxod = obway->content_size;
			ft_printf("kolway %d\n", kolway);
			kolway = 0;
			ft_printf("proxod %zu\n", proxod);
		}
		way = obway->content;
		while(way)
		{
			read = way->content;
			ft_printf("way %s\n", read->name);
			way = way->next;
		}
		ft_printf("!!!!!!!!!!\n");
		kolway++;
		obway = obway->next;
	}
	ft_printf("kolway %d\n", kolway);
}

int		main(int ac, char **av)
{
	t_map	map;
	t_list	*t;
	t_room	*read;
	int		fd;
	int i;

	ac = 0;
	i = 0;
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
	ft_printf("########\n");
	map.rooms[0]->f = 1;
	while (map.rooms[i])
	{
		map.rooms[i]->n = i;
		map.rooms[i]->gl = -1;
		i++;
	}
	way(&map);
	ft_printway(map.way);
	return (0);
}