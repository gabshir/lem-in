/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillem- <jwillem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 17:03:40 by jwillem-          #+#    #+#             */
/*   Updated: 2019/05/12 15:02:22 by jwillem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"



void	way(t_map *map, int l)
{
	int i;
	t_list *combnow;

	combnow = NULL;
	i = 0;
	while (shirina(map) == 1)
	{
		ft_saveway(&map->end, &combnow, 0);
		restorroom(map);
	}
	if (combnow != NULL)
	{
		ft_lstpush(&map->way, ft_lstnew_ptr(combnow));
		ft_konnekt(&map->way, l);
		combnow = NULL;
	}
	restisp(&map->way);
	restorroom(map);
	while (shirinablok(map) == 1 && i == 0)
	{
		ft_saveway(&map->end, &combnow, 1);
		restorroom(map);
		i = path_analysis(&map->way);
	}
	ft_lstpush(&map->cut, ft_lstnew_ptr(combnow));
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