/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   superposition.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabshire <gabshire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 21:25:15 by gabshire          #+#    #+#             */
/*   Updated: 2019/05/11 21:25:15 by gabshire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void super_position(t_map *map)
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
	ft_lstpush(&map->way, ft_lstnew_ptr(combnow));
	ft_konnekt(&map->way, l);
	combnow = NULL;
	restisp(&map->way);
	restorroom(map);
}