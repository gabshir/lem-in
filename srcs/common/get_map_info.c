/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillem- <jwillem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 19:23:43 by gabshire          #+#    #+#             */
/*   Updated: 2019/05/21 08:52:58 by jwillem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	quantity_of_ants(t_map *map, char *line, int print)
{
	char	*str;

	if (ft_strcmp(line, "##end") == 0 || ft_strcmp(line, "##start") == 0)
	{
		ft_printf("ERROR COMMAND\n");
		free(line);
		exit(1);
	}
	map->ants = ft_atoi(line);
	str = ft_itoa(map->ants);
	if (line[0] && line[0] == '#')
		return ;
	if (ft_strcmp(str, line) != 0 || map->ants < 1)
	{
		ft_printf(ER "Incorrect number of ants!");
		exit(1);
	}
	(print) ? ft_printf("%s\n", line) : 0;
	(str) ? free(str) : 0;
	str = NULL;
}

void	start_map_info(t_map *map, char *line, int print)
{
	while (map->ants == 0 && get_next_line(0, &line) == 1)
	{
		quantity_of_ants(map, line, print);
		free(line);
		line = NULL;
	}
}

void	organize_room
	(t_sort *time_to_sort, t_map *map, char *line, t_list *room_list)
{
	if (*time_to_sort == not_sorted)
	{
		if (map->end.name == NULL || map->start.name == NULL)
		{
			ft_printf(ER "Start or Finish not found \n");
			exit(1);
		}
		map->rooms = sorted_rooms_ptr_array(map, &room_list);
		check_name_duplicates(map);
	}
	(*time_to_sort) = sorted;
	organize_links(map, line);
}

int		lstadd_room
	(t_sort time_to_sort, t_list **room_list, t_map *map, char *line)
{
	if (time_to_sort == sorted)
	{
		ft_printf(ER "No more rooms after connections have started!\n");
		exit(1);
	}
	ft_lstadd(room_list, ft_lstnew_ptr(create_room(map, line)));
	return (0);
}

void	get_map_info(t_map *map, int print)
{
	char	*line;
	t_list	*room_list;
	t_sort	time_to_sort;

	room_list = NULL;
	line = NULL;
	time_to_sort = not_sorted;
	start_map_info(map, line, print);
	while (get_next_line(0, &line) > 0 && ft_strlen(line))
	{
		print && ft_printf("%s\n", line);
		if (chec_start_finish(map, line, print) == 1)
			continue ;
		if (ft_strchr(line, ' ') && ft_strncmp(line, "#", 1)
			&& (lstadd_room(time_to_sort, &room_list, map, line) == 1))
			continue ;
		(ft_strchr(line, '-') && ft_strncmp(line, "#", 1)) ?
		organize_room(&time_to_sort, map, line, room_list) : 0;
		free(line);
		line = NULL;
	}
	(line) ? free(line) : 0;
}
