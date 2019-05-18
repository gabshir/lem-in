/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillem- <jwillem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 19:32:56 by jwillem-          #+#    #+#             */
/*   Updated: 2019/05/18 22:37:52 by jwillem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

// for test

void	v_start_init(int fd, t_map *map, char *line, int print)
{
	if (map->start.name == NULL)
	{
		if (get_next_line(fd, &line) > 0)
		{
			print && ft_printf("%s\n", line);
			if (check_hash(line, "##end", "##start") == 0)
			{
				free(line);
				line = NULL;
				start_init(map, line, print);
			}
			if (map->start.name == NULL)
			{
				map->start.links = NULL;
				room_name_and_coords(&map->start, line);
				map->room_q++;
			}
		}
		else
			error_specify_room("Start");
		free(line);
	}
	else
		dublication_room("Start");
}

void	v_end_init(int fd, t_map *map, char *line, int print)
{
	if (map->end.name == NULL)
	{
		if (get_next_line(fd, &line) > 0)
		{
			print && ft_printf("%s\n", line);
			if (check_hash(line, "##end", "##start") == 0)
			{
				free(line);
				line = NULL;
				end_init(map, line, print);
			}
			if (map->end.name == NULL)
			{
				map->end.links = NULL;
				room_name_and_coords(&map->end, line);
				map->room_q++;
			}
		}
		else
			error_specify_room("End");
		free(line);
	}
	else
		dublication_room("End");
}

// for test

void 	start_vis_info(int fd, t_map *map, char *line, int print)
{
	while (map->ants == 0 && get_next_line(fd, &line) == 1)
	{
		quantity_of_ants(map, line, print);
		free(line);
		line = NULL;
	}
}

// for test

void	get_vis_info(int fd, t_map *map, int print)
{
	char	*line;
	t_list	*room_list;
	e_sort	time_to_sort;

	room_list = NULL;
	line = NULL;
	time_to_sort = not_sorted;
	start_vis_info(fd, map, line, print);	//test
	while (get_next_line(fd, &line) > 0)
	{
		print && ft_printf("%s\n", line);
		if (!ft_strcmp(line, "##start"))
			v_start_init(fd, map, line, print);	// test
		else if (!ft_strcmp(line, "##end"))
			v_end_init(fd, map, line, print);	// test
		else if (ft_strchr(line, ' ') && ft_strncmp(line, "#", 1))
		{
			if (lstadd_room(time_to_sort, &room_list, map, line) == 1)
				continue ;
		}
		else if (ft_strchr(line, '-') && ft_strncmp(line, "#", 1))
			organize_room(&time_to_sort, map, line, room_list);
		else if (!print && !ft_strlen(line))
			break ;
		free(line);
		line = NULL;
	}
	if (line)
		free(line);
}
