/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillem- <jwillem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 05:19:07 by jwillem-          #+#    #+#             */
/*   Updated: 2019/05/21 07:24:41 by jwillem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static char	*get_ant_name(char *str)
{
	int		len;
	int		i;
	char	*number;

	len = 0;
	i = 1;
	while (str[i++] != '-')
		len++;
	SECURE_MALLOC(number = malloc(sizeof(char) * (len + 1)));
	number[len] = '\0';
	str = ft_strchr(str, '-') - 1;
	while (--len >= 0)
		number[len] = *str--;
	return (number);
}

static void	set_goal_for_ant(t_map *map, t_ant *ant)
{
	if (!ft_strcmp(ant->r_curr->name, ROOMS[ROOM_Q - 1]->name))
		ant->finished = 1;
	ant->x = ant->x2;
	ant->y = ant->y2;
	ant->x2 = ant->r_curr->x * map->mlx.x_len;
	ant->y2 = ant->r_curr->y * map->mlx.y_len;
	ant->hyp = sqrt(pow(ant->y2 - ant->y, 2) + pow(ant->x2 - ant->x, 2));
	ant->sin = (ant->y2 - ant->y) / ant->hyp;
	ant->cos = (ant->x2 - ant->x) / ant->hyp;
	map->mlx.movement = 1;
	map->mlx.delta = 0;
}

static void	refresh_ants(t_map *map, char **ants)
{
	t_room	*room;
	char	*r_name;
	char	*ant_name;
	t_ant	*ant;

	map->mlx.step++;
	while (*ants)
	{
		r_name = ft_strchr(*ants, '-') + 1;
		if (!ft_strcmp(r_name, map->end.name))
			room = ROOMS[ROOM_Q - 1];
		else
			room = find_room_by_name(map, r_name, 1, ROOM_Q - 1);
		ant_name = get_ant_name(*ants++);
		ant = &map->mlx.ants[ft_atoi(ant_name) - 1];
		free(ant_name);
		ant->r_curr = room;
		set_goal_for_ant(map, ant);
	}
}

int			press_space(int key, t_map *map)
{
	char	*line;
	char	**ants;

	if (key == 49)
	{
		if (get_next_line(0, &line) > 0)
		{
			ants = ft_strsplit(line, ' ');
			draw_map(map);
			refresh_ants(map, ants);
			freesplit(ants);
			free(line);
		}
	}
	return (0);
}
