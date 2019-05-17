/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rooms.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillem- <jwillem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 20:09:44 by jwillem-          #+#    #+#             */
/*   Updated: 2019/05/17 13:25:59 by gabshire         ###   ########.fr       */
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

void	check_hash(char *line, char *edge, char *counter_edge)
{
	if (!ft_strncmp(line, "#", 1))
	{
		if (!ft_strcmp(line, counter_edge))
			ft_printf(ER "Start & End rooms must not be the same one!\n");
		else if (!ft_strcmp(line, edge))
			ft_printf(ER "What do you need 2 %s-lines in a row for?\n", edge);
		else if (!ft_strncmp(line, "##", 2))
			ft_printf(ER "No other ##lines allowed, esp-ly after %s.\n", edge);
		else
			ft_printf(ER "Put comment above the %s-line, please.\n", edge);
		exit(1);
	}
}

void	start_init(t_map *map, char *line)
{
	if (map->start.name == NULL)
	{
		if (get_next_line(0, &line) > 0)
		{
			ft_printf("%s\n", line);
			check_hash(line, "##start", "##end");
			map->start.links = NULL;
			map->start.isp = 0;
			room_name_and_coords(&map->start, line);
			map->start.f = 1;
			map->room_q++;
		}
		else
		{
			ft_printf(ER "You didn't specify the Start room.\n");
			exit(1);
		}
		free(line);
	}
	else
	{
		ft_printf(ER "You've already specified the Start room.\n");
		exit(1);
	}
}

void	end_init(t_map *map, char *line)
{
	if (map->end.name == NULL)
	{
		if (get_next_line(0, &line) > 0)
		{
			ft_printf("%s\n", line);
			check_hash(line, "##end", "##start");
			map->end.links = NULL;
			map->end.f = 0;
			map->end.isp = 0;
			room_name_and_coords(&map->end, line);
			map->room_q++;
		}
		else
		{
			ft_printf(ER "You didn't specify the Start room.\n");
			exit(1);
		}
		free(line);
	}
	else
	{
		ft_printf(ER "You've already specified the End room.\n");
		exit(1);
	}
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
