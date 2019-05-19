/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillem- <jwillem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 17:03:40 by jwillem-          #+#    #+#             */
/*   Updated: 2019/05/19 04:09:05 by gabshire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	ft_konnekt(t_list **links, size_t i)
{
	t_list	*temp;

	temp = *links;
	while (temp->next)
		temp = temp->next;
	temp->content_size = i;
}

static void	up_way(t_map *map, int l)
{
	t_list	*combnow;

	combnow = NULL;
	while (shirina(map) == 1)
	{
		ft_saveway(&map->end, &combnow, 0, map->end.gl);
		restorroom(map);
	}
	if (combnow != NULL)
	{
		ft_lstpush(&map->way, ft_lstnew_ptr(combnow));
		ft_konnekt(&map->way, l);
		combnow = NULL;
	}
}

static int	up_cutway(t_map *map)
{
	t_list	*combnow;
	int		i;

	combnow = NULL;
	i = 0;
	map->start.gl = 0;
	map->start.f = 1;
	while (shirinablok(map) == 1 && i == 0)
	{
		map->start.gl = 0;
		map->start.f = 1;
		map->end.isp = 1;
		ft_saveway(&map->end, &combnow, 1, map->end.gl);
		restorroom(map);
		i = path_analysis(&map->way);
	}
	if (combnow)
		ft_lstpush(&map->cut, ft_lstnew_ptr(combnow));
	return (i);
}

void		way(t_map *map, int l)
{
	int	i;

	map->start.isp = 0;
	map->start.f = 1;
	map->end.f = 0;
	map->end.isp = 0;
	up_way(map, l);
	restisp(&map->way);
	restorroom(map);
	i = up_cutway(map);
	restisp(&map->cut);
	restornap(&map->way);
	restornap(&map->cut);
	freeway(&map->cut);
	restorroom(map);
	if (i == 1)
	{
		l = l + 1;
		way(map, l);
	}
}
