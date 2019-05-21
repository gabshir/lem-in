/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillem- <jwillem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 05:27:01 by jwillem-          #+#    #+#             */
/*   Updated: 2019/05/21 08:38:43 by jwillem-         ###   ########.fr       */
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

static void	hypotenuse(t_map *map, size_t i, t_line l, t_room *linked)
{
	while (l.curr_center / W_WIDTH != l.next_center / W_WIDTH)
	{
		map->mlx.pic.data[l.pix] = COMMON;
		if (l.passed)
			draw_pipe(map, l.prev, l.pix);
		l.curr_center = ROOMS[i]->y < linked->y ? \
			l.curr_center + W_WIDTH : l.curr_center - W_WIDTH;
		l.passed++;
		l.prev = l.pix;
		if (ROOMS[i]->x < linked->x)
			l.pix = l.curr_center + ABS(l.passed * \
				((ROOMS[i]->x - linked->x) * map->mlx.x_len) / \
				((ROOMS[i]->y - linked->y) * map->mlx.y_len));
		else
			l.pix = l.curr_center - ABS(l.passed * \
				((ROOMS[i]->x - linked->x) * map->mlx.x_len) / \
				((ROOMS[i]->y - linked->y) * map->mlx.y_len));
	}
}

void		draw_line(t_map *map, size_t i, int curr_cntr, t_room *linked)
{
	t_line	l;

	l.curr_center = curr_cntr;
	l.next_center = W_WIDTH * (INDENT + linked->y * map->mlx.y_len - 1) \
		+ INDENT + linked->x * map->mlx.x_len - 1;
	l.passed = 0;
	l.pix = curr_cntr;
	l.i = i;
	if (ROOMS[i]->x != linked->x && ROOMS[i]->y != linked->y)
		hypotenuse(map, i, l, linked);
	else if (ROOMS[i]->x == linked->x && ROOMS[i]->y != linked->y)
		while (l.pix != l.next_center)
		{
			map->mlx.pic.data[l.pix] = COMMON;
			l.pix = ROOMS[i]->y < linked->y ? l.pix + W_WIDTH : l.pix - W_WIDTH;
		}
	else if (ROOMS[i]->x != linked->x && ROOMS[i]->y == linked->y)
		while (l.pix != l.next_center)
		{
			map->mlx.pic.data[l.pix] = COMMON;
			ROOMS[i]->x < linked->x ? l.pix++ : l.pix--;
		}
}
