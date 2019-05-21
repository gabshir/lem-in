/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillem- <jwillem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 16:53:55 by jwillem-          #+#    #+#             */
/*   Updated: 2019/05/21 05:27:23 by jwillem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

// static void	draw_pipe(t_map *map, int prev, int pix)
// {
// 	if (ABS(prev - pix) < W_WIDTH && prev > pix)
// 		while (prev - pix < W_WIDTH)
// 			map->mlx.pic.data[prev++] = COMMON;
// 	else if (ABS(prev - pix) < W_WIDTH && prev < pix)
// 		while (pix - prev < W_WIDTH)
// 			map->mlx.pic.data[prev--] = COMMON;
// 	else if (ABS(prev - pix) > W_WIDTH && prev > pix)
// 		while (prev - pix > W_WIDTH)
// 			map->mlx.pic.data[prev--] = COMMON;
// 	else if (ABS(prev - pix) > W_WIDTH && prev < pix)
// 		while (pix - prev > W_WIDTH)
// 			map->mlx.pic.data[prev++] = COMMON;
// }

// void		draw_line(t_map *map, size_t i, int curr_center, t_room *linked)
// {
// 	int	next_center;
// 	int	passed;
// 	int	pix;
// 	int	prev;

// 	next_center = W_WIDTH * (INDENT + linked->y * map->mlx.y_len - 1) \
// 		+ INDENT + linked->x *  map->mlx.x_len - 1;
// 	passed = 0;
// 	pix = curr_center;
// 	if (ROOMS[i]->x != linked->x && ROOMS[i]->y != linked->y)
// 		while (curr_center / W_WIDTH != next_center / W_WIDTH)
// 		{
// 			map->mlx.pic.data[pix] = COMMON;
// 			if (passed)
// 				draw_pipe(map, prev, pix);
// 			curr_center = ROOMS[i]->y < linked->y ? curr_center + W_WIDTH : curr_center - W_WIDTH;
// 			passed++;
// 			prev = pix;
// 			if (ROOMS[i]->x < linked->x)
// 				pix = curr_center + ABS(passed * ((ROOMS[i]->x - linked->x) * map->mlx.x_len) / ((ROOMS[i]->y - linked->y) * map->mlx.y_len));
// 			else
// 				pix = curr_center - ABS(passed * ((ROOMS[i]->x - linked->x) * map->mlx.x_len) / ((ROOMS[i]->y - linked->y) * map->mlx.y_len));
// 		}
// 	else if (ROOMS[i]->x == linked->x && ROOMS[i]->y != linked->y)
// 		while (pix != next_center)
// 		{
// 			map->mlx.pic.data[pix] = COMMON;
// 			pix = ROOMS[i]->y < linked->y ? pix + W_WIDTH : pix - W_WIDTH;
// 		}
// 	else if (ROOMS[i]->x != linked->x && ROOMS[i]->y == linked->y)
// 		while (pix != next_center)
// 		{
// 			map->mlx.pic.data[pix] = COMMON;
// 			ROOMS[i]->x < linked->x ? pix++ : pix--;
// 		}
// }

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

static int	close_win(int i)
{
	exit(i);
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

static void	visualization(t_map *map)
{	
	map_mlx_init(map);
	init_ants(map);
	draw_map(map);
	mlx_loop_hook(map->mlx.mlx_ptr, draw_ants, map);
	mlx_key_hook(map->mlx.win, press_space, map);
	mlx_hook(map->mlx.win, 17, 1L << 17, close_win, 0);
	
	mlx_loop(map->mlx.mlx_ptr);
}

static void	map_vis_init(t_map *map)
{
	map->ants = 0;
	map->start.name = NULL;
	map->end.name = NULL;
	map->room_q = 0;
	map->rooms = NULL;
	map->way = NULL;
	map->cut = NULL;
}

int	main(int ac, char **av)
{
	t_map	map;

	map.fd = open(av[1], O_RDONLY);	
	ac = 0;
	map_vis_init(&map);	//test
	// get_map_info(&map, 0);
	get_vis_info(map.fd, &map, 0); // test
	visualization(&map);
	return (0);
}
