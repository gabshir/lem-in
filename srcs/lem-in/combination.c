/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   combination.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillem- <jwillem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 21:12:15 by jwillem-          #+#    #+#             */
/*   Updated: 2019/05/18 22:19:14 by jwillem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static size_t	check_best_global_comb(t_map *map, t_list *comb_ptr)
{
	t_list	*way;
	size_t	comb_number;
	int		sum_len;
	int		cur_steps;
	int		way_q;

	way = comb_ptr->content;
	sum_len = 0;
	way_q = 0;
	while (way)
	{
		sum_len += ft_lstlen(way->content) - 1;
		cur_steps = (map->ants + sum_len - 1) / ++way_q;
		if (cur_steps < C_STEPS)
		{
			comb_number = comb_ptr->content_size;
			C_QUANT = way_q;
			C_STEPS = cur_steps;
			C_SUM_LEN = sum_len;
		}
		way = way->next;
	}
	return (comb_number);
}

static t_list	*find_best_global_comb(t_map *map)
{
	t_list	*comb_ptr;
	size_t	comb_number;

	comb_ptr = map->way;
	C_STEPS = INT_MAX;
	while (comb_ptr)
	{
		comb_number = check_best_global_comb(map, comb_ptr);
		comb_ptr = comb_ptr->next;
	}
	comb_ptr = map->way;
	while (comb_ptr->content_size != comb_number)
		comb_ptr = comb_ptr->next;
	return (comb_ptr);
}

void			make_best_combination(t_map *map)
{
	t_list	*way;
	t_list	*ptr;
	int		way_q;
	int		i;

	way = find_best_global_comb(map)->content;
	SECURE_MALLOC(C_WAY = ft_memalloc(sizeof(t_path) * (C_QUANT + 1)));
	way_q = -1;
	while (++way_q < C_QUANT)
	{
		C_WAY[way_q].len = ft_lstlen(way->content) - 1;
		SECURE_MALLOC(C_WAY[way_q].rooms = \
			ft_memalloc(sizeof(t_room*) * (C_WAY[way_q].len + 1)));
		ptr = way->content;
		i = -1;
		while (ptr->next)
		{
			C_WAY[way_q].rooms[++i] = ptr->next->content;
			ptr = ptr->next;
		}
		way = way->next;
	}
}
