/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rooms.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillem- <jwillem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 20:09:44 by jwillem-          #+#    #+#             */
/*   Updated: 2019/05/19 02:07:15 by jwillem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	validate_axis(t_room *room, char *splitstr, char axis)
{
	char	*str;
	int f;

	f = 0;
	if (splitstr == NULL)
		f = 1;
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

void	room_name_and_coords(t_room *room, char *line)
{
	char	**split;

	split = ft_strsplit(line, ' ');
	room->name = ft_strdup(split[0]);
	if (!ft_strncmp(room->name, "L", 1) || ft_strchr(room->name, '-'))
	{
		ft_printf(ER "Illegal room name.\n");
		exit(1);
	}
	room->x = 0;
	room->y = 0;
	validate_axis(room, split[1], 'X');
	validate_axis(room, split[2], 'Y');
	room->f = 0;
	room->gl = -1;
	room->ant_num = 0;
	if (split[3])
	{
		ft_printf(ER "You've entered excess info about room %s.\n", room->name);
		exit(1);
	}
	freesplit(split);
}

int		check_hash(char *line, char *edge, char *counter_edge)
{
	if (!ft_strcmp(line, counter_edge))
	{
		ft_printf(ER "Start & End rooms must not be the same one!\n");
		exit(1);
	}
	else if (!ft_strcmp(line, edge))
	{
		ft_printf(ER "What do you need 2 %s-lines in a row for?\n", edge);
		exit(1);
	}
	else if (line[0] && line[0] == '#')
		return (0);
	return (1);
}

void	start_init(t_map *map, char *line, int print)
{
	if (map->start.name == NULL)
	{
		if (get_next_line(0, &line) > 0)
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

void	end_init(t_map *map, char *line, int print)
{
	if (map->end.name == NULL)
	{
		if (get_next_line(0, &line) > 0)
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

t_room	*create_room(t_map *map, char *line)
{
	t_room *new;

	new = NULL;
	if (!(new = (t_room *)malloc(sizeof(t_room))))
	{
		ft_printf(ER "Couldn't allocate memory.\n");
		exit(1);
	}
	new->f = -1;
	new->links = NULL;
	new->isp = 0;
	room_name_and_coords(new, line);
	map->room_q++;
	return (new);
}
