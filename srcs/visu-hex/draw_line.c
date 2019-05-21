/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillem- <jwillem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 05:27:01 by jwillem-          #+#    #+#             */
/*   Updated: 2019/05/21 05:27:26 by jwillem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	draw_pipe(t_map *map, int prev, int pix)
{
	if (ABS(prev - pix) < W_WIDTH && prev > pix)
		while (prev - pix < W_WIDTH)
			map->mlx.pic.data[prev++] = COMMON;
	else if (ABS(prev - pix) < W_WIDTH && prev < pix)
		while (pix - prev < W_WIDTH)
			map->mlx.pic.data[prev--] = COMMON;
	else if (ABS(prev - pix) > W_WIDTH && prev > pix)
		while (prev - pix > W_WIDTH)
			map->mlx.pic.data[prev--] = COMMON;
	else if (ABS(prev - pix) > W_WIDTH && prev < pix)
		while (pix - prev > W_WIDTH)
			map->mlx.pic.data[prev++] = COMMON;
}

void		draw_line(t_map *map, size_t i, int curr_center, t_room *linked)
{
	int	next_center;
	int	passed;
	int	pix;
	int	prev;

	next_center = W_WIDTH * (INDENT + linked->y * map->mlx.y_len - 1) \
		+ INDENT + linked->x *  map->mlx.x_len - 1;
	passed = 0;
	pix = curr_center;
	if (ROOMS[i]->x != linked->x && ROOMS[i]->y != linked->y)
		while (curr_center / W_WIDTH != next_center / W_WIDTH)
		{
			map->mlx.pic.data[pix] = COMMON;
			if (passed)
				draw_pipe(map, prev, pix);
			curr_center = ROOMS[i]->y < linked->y ? curr_center + W_WIDTH : curr_center - W_WIDTH;
			passed++;
			prev = pix;
			if (ROOMS[i]->x < linked->x)
				pix = curr_center + ABS(passed * ((ROOMS[i]->x - linked->x) * map->mlx.x_len) / ((ROOMS[i]->y - linked->y) * map->mlx.y_len));
			else
				pix = curr_center - ABS(passed * ((ROOMS[i]->x - linked->x) * map->mlx.x_len) / ((ROOMS[i]->y - linked->y) * map->mlx.y_len));
		}
	else if (ROOMS[i]->x == linked->x && ROOMS[i]->y != linked->y)
		while (pix != next_center)
		{
			map->mlx.pic.data[pix] = COMMON;
			pix = ROOMS[i]->y < linked->y ? pix + W_WIDTH : pix - W_WIDTH;
		}
	else if (ROOMS[i]->x != linked->x && ROOMS[i]->y == linked->y)
		while (pix != next_center)
		{
			map->mlx.pic.data[pix] = COMMON;
			ROOMS[i]->x < linked->x ? pix++ : pix--;
		}
}
