/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillem- <jwillem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 16:53:55 by jwillem-          #+#    #+#             */
/*   Updated: 2019/05/21 07:24:30 by jwillem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	coor_len(t_room **rooms, char axis, int indent)
{
	int	i;
	int	max;
	int	coor;
	int	len;
	int	facet;

	i = 0;
	max = axis == 'x' ? rooms[i]->x : rooms[i]->y;
	facet = axis == 'x' ? W_WIDTH : W_HEIGHT;
	while (rooms[++i])
	{
		coor = axis == 'x' ? rooms[i]->x : rooms[i]->y;
		if (coor > max)
			max = coor;
	}
	if (!max)
		max = 1;
	len = (facet - 2 * indent) / max;
	return (len);
}

static int	close_win(void)
{
	exit(1);
}

static void	map_mlx_init(t_map *map)
{
	map->mlx.mlx_ptr = mlx_init();
	map->mlx.win = mlx_new_window(map->mlx.mlx_ptr, W_WIDTH, W_HEIGHT, \
		"The Map.");
	map->mlx.pic.img_ptr = mlx_new_image(map->mlx.mlx_ptr, W_WIDTH, W_HEIGHT);
	map->mlx.pic.data = (int *)mlx_get_data_addr(map->mlx.pic.img_ptr, \
		&map->mlx.pic.bpp, &map->mlx.pic.size_l, &map->mlx.pic.endian);
	map->mlx.indent = 50;
	map->mlx.x_len = coor_len(map->rooms, 'x', map->mlx.indent);
	map->mlx.y_len = coor_len(map->rooms, 'y', map->mlx.indent);
}

static void	init_ants(t_map *map)
{
	int	i;
	int	number;

	SECURE_MALLOC(map->mlx.ants = ft_memalloc(sizeof(t_ant) * map->ants));
	i = -1;
	number = 0;
	map->mlx.movement = 1;
	map->mlx.step = 0;
	while (++i < map->ants)
	{
		map->mlx.ants[i].r_curr = ROOMS[0];
		map->mlx.ants[i].name = ft_itoa(++number);
		map->mlx.ants[i].x2 = ROOMS[0]->x * map->mlx.x_len;
		map->mlx.ants[i].y2 = ROOMS[0]->y * map->mlx.y_len;
		map->mlx.ants[i].x = map->mlx.ants[i].x2;
		map->mlx.ants[i].y = map->mlx.ants[i].y2;
		map->mlx.ants[i].finished = 0;
	}
}

int			main(void)
{
	t_map	map;

	ft_bzero(&map, sizeof(map));
	get_map_info(&map, 0);
	map_mlx_init(&map);
	init_ants(&map);
	draw_map(&map);
	mlx_loop_hook(map.mlx.mlx_ptr, draw_ants, &map);
	mlx_key_hook(map.mlx.win, press_space, &map);
	mlx_hook(map.mlx.win, 17, 1L << 17, close_win, NULL);
	mlx_loop(map.mlx.mlx_ptr);
	return (0);
}
