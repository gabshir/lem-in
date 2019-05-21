/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vis_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillem- <jwillem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 04:55:52 by jwillem-          #+#    #+#             */
/*   Updated: 2019/05/21 05:18:23 by jwillem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	draw_one_ant(t_map *map, t_ant *ant, int delta)
{
	if (delta > ant->hyp)
	{
		if (ant->finished)
		{
			ant->x = ant->x2;
			ant->y = ant->y2;
			ant->cos = 0;
			ant->sin = 0;
		}
		delta = ant->hyp;
	}
	mlx_string_put(map->mlx.mlx_ptr, map->mlx.win,
		round(ant->x + delta * ant->cos) + INDENT,
		round(ant->y + delta * ant->sin) + INDENT,
		ANT, ant->name);
	return (delta < ant->hyp);
}

int     draw_ants(t_map *map)
{
	int i;

	if (map->mlx.movement)
	{
		i = -1;
		draw_map(map);
		map->mlx.movement = 0;
		while (++i < map->ants)
			map->mlx.movement += \
				draw_one_ant(map, &map->mlx.ants[i], map->mlx.delta);
		map->mlx.delta += 3;
	}
	return (0);
}
