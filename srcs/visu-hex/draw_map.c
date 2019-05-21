/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillem- <jwillem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 05:22:53 by jwillem-          #+#    #+#             */
/*   Updated: 2019/05/21 05:24:08 by jwillem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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

static void	draw_one_room(t_map *map, size_t i)
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

static void	draw_links(t_map *map, size_t i)
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
    size_t	i;

	i = 0;
	while (map->rooms[i])
	{
		draw_one_room(map, i);
		draw_links(map, i++);
	}
}

int		    draw_map(t_map *map)
{
    int	i;
	char	*step;
	
	i = -1;
	draw_back(map);
    draw_rooms(map);
	step = ft_itoa(map->mlx.step);
	step = ft_strjoin_free("Step № ", step, 2);
	mlx_put_image_to_window(map->mlx.mlx_ptr, map->mlx.win, \
		map->mlx.pic.img_ptr, 0, 0);
	while (ROOMS[++i])
		mlx_string_put(map->mlx.mlx_ptr, map->mlx.win, \
			ROOMS[i]->x * map->mlx.x_len + INDENT / 2, \
			ROOMS[i]->y * map->mlx.y_len + INDENT * 3 / 2, \
			NAME, ROOMS[i]->name);
	mlx_string_put(map->mlx.mlx_ptr, map->mlx.win, \
		INDENT, W_HEIGHT - INDENT, NAME, step);
	free(step);
	return (1);
}
