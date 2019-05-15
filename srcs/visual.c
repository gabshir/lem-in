/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillem- <jwillem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 16:53:55 by jwillem-          #+#    #+#             */
/*   Updated: 2019/05/15 13:37:08 by gabshire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

// здесь все для орисовки карты

static void	draw_back(t_map *map)
{
	int	h;
	int	w;

	h = -1;
	while (++h < W_HEIGHT)
	{
		w = -1;
		while (++w < W_WIDTH)
			map->mlx.pic.data[h * W_WIDTH + w] = BACK;
	}
}

static void	draw_one_room(t_map *map, int i)
{
	int	center;
	int	from;
	int	to;
	int	pix;
	int	line;

	center = W_WIDTH * (INDENT + ROOMS[i]->y * map->mlx.y_len - 1) \
		+ INDENT + ROOMS[i]->x * map->mlx.x_len - 1;
	from = center - (W_WIDTH + 1) * map->mlx.indent / 2;
	pix = from;
	line = 0;
	to = center + (W_WIDTH + 1) * map->mlx.indent / 2;
	while (pix <= to)
	{
		while (pix <= to - (map->mlx.indent * W_WIDTH) + line)
			if (i == 0)
				map->mlx.pic.data[pix++] = START;
			else if (i == map->room_q - 1)
				map->mlx.pic.data[pix++] = END;
			else
				map->mlx.pic.data[pix++] = COMMON;
		line += W_WIDTH;
		pix = from + line;
	}
}

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

static void	draw_line(t_map *map, int i, int curr_center, t_room *linked)
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

static void	draw_links(t_map *map, int i)
{
	int		curr_center;
	t_list	*ptr;

	curr_center = W_WIDTH * (INDENT + ROOMS[i]->y * map->mlx.y_len - 1) \
		+ INDENT + map->rooms[i]->x *  map->mlx.x_len - 1;
	ptr = ROOMS[i]->links;
	while (ptr)
	{
		draw_line(map, i, curr_center, (t_room*)ptr->content);
		ptr = ptr->next;
	}
}

static void	draw_rooms(t_map *map)
{
    int	i;

	i = 0;
	while (map->rooms[i])
	{
		draw_one_room(map, i);
		draw_links(map, i++);
	}
}

static int	visual_hook(t_map *map)
{
    int	i;
	
	i = -1;
	draw_back(map);
    draw_rooms(map);
	mlx_put_image_to_window(map->mlx.mlx_ptr, map->mlx.win, \
		map->mlx.pic.img_ptr, 0, 0);
	while (ROOMS[++i])
		mlx_string_put(map->mlx.mlx_ptr, map->mlx.win, \
			ROOMS[i]->x * map->mlx.x_len + INDENT / 2, \
			ROOMS[i]->y * map->mlx.y_len + INDENT * 3 / 2, \
			NAME, ROOMS[i]->name);
	return (1);
}

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

void   		visualization(t_map *map)
{
    map->mlx.mlx_ptr = mlx_init();
	map->mlx.win = mlx_new_window(map->mlx.mlx_ptr, W_WIDTH, W_HEIGHT, \
		"The Map.");
	map->mlx.pic.img_ptr = mlx_new_image(map->mlx.mlx_ptr, W_WIDTH, W_HEIGHT);
	map->mlx.pic.data = (int *)mlx_get_data_addr(map->mlx.pic.img_ptr, \
		&map->mlx.pic.bpp, &map->mlx.pic.size_l, &map->mlx.pic.endian);
	// stk->mlx.int_height = W_HEIGHT / stk->alen;
	map->mlx.indent = 50;
	map->mlx.x_len = coor_len(map->rooms, 'x', map->mlx.indent);
	map->mlx.y_len = coor_len(map->rooms, 'y', map->mlx.indent);
	// stk->mlx.int_width = W_WIDTH / 2 / max_abs(stk) - 1;
	mlx_loop_hook(map->mlx.mlx_ptr, visual_hook, map);
	mlx_hook(map->mlx.win, 17, 1L << 17, close_win, 0);
	mlx_loop(map->mlx.mlx_ptr);
}
