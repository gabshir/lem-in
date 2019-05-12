/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ant_flow.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillem- <jwillem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 18:24:28 by jwillem-          #+#    #+#             */
/*   Updated: 2019/05/12 19:39:27 by jwillem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

// static void	combinations_memalloc(t_map *map)
// {
// 	int		mem;
// 	int		i;
// 	int		w_idx;
// 	t_list	*comb;
// 	t_list	*path;

// 	mem = ft_lstlen(map->way) + 1;
// 	SECURE_MALLOC(map->comb = (t_comb*)ft_memalloc(sizeof(t_comb) * mem));
// 	i = -1;
// 	comb = map->way;
// 	while (++i < mem - 1 && comb)
// 	{
// 		path = comb->content;
// 		map->comb[i].quant = ft_lstlen(path);
// 		map->comb[i].sum_len = 0;
// 		SECURE_MALLOC(map->comb[i].way_arr = (t_list**)ft_memalloc(sizeof(t_list*) * (map->comb[i].quant + 1)));
// 		w_idx = 0;
// 		while (path)
// 		{
// 			map->comb[i].sum_len += ft_lstlen(path->content) - 1;
// 			map->comb[i].way_arr[w_idx++] = path->content;
// 			path = path->next;
// 		}
// 		map->comb[i].steps = (map->ants + map->comb[i].sum_len - 1) / map->comb[i].quant;
// 		comb = comb->next;
// 	}
// }

// static t_comb	*choose_combination(t_map *map)
// {
// 	t_comb	*comb;
// 	int	i;
// 	int	min;
	
// 	i = -1;
// 	min = INT_MAX;
// 	// comb = &map->comb[i];
// 	while (map->comb[++i].steps)
// 	{
// 		if (map->comb[i].steps < min)
// 		{
// 			min = map->comb[i].steps;
// 			comb = &map->comb[i];
// 		}
// 	}
// 	return (comb);
// }

// static void	make_best_combination(t_map *map, t_comb *comb)
// {
// 	int		cur_steps;
// 	int		sum_len;
// 	int		w_idx;
// 	int		comb_idx;
// 	int		rem_comb_idx;

// 	comb_idx = -1;
// 	comb->steps = INT_MAX;
// 	while (map->comb[++comb_idx].steps)
// 	{
// 		w_idx = -1;
// 		sum_len = 0;
// 		while (map->comb[comb_idx].way_arr[++w_idx])
// 		{
// 			sum_len += ft_lstlen(map->comb[comb_idx].way_arr[w_idx]) - 1;
// 			cur_steps = (map->ants + sum_len - 1) / (w_idx + 1);
// 			if (cur_steps < comb->steps)
// 			{
// 				rem_comb_idx = comb_idx;
// 				comb->quant = w_idx + 1;
// 				comb->steps = cur_steps;
// 				comb->sum_len = sum_len;
// 			}
// 		}
// 	}
// 	SECURE_MALLOC(comb->way_arr = /*(t_list**)*/ft_memalloc(sizeof(t_list*) * (comb->quant + 1)));
// 	w_idx = -1;
// 	while (++w_idx < comb->quant)
// 		comb->way_arr[w_idx] = map->comb[rem_comb_idx].way_arr[w_idx];
// }

static void	make_best_combination(t_map *map/*, t_comb *comb*/)
{
	t_list	*comb_ptr;
	t_list	*way;
	size_t	comb_number;
	int		sum_len;
	int		cur_steps;
	int		way_q;

	comb_ptr = map->way;
	map->comb.steps = INT_MAX;
	while (comb_ptr)
	{
		way = comb_ptr->content;
		sum_len = 0;
		way_q = 0;
		while (way)
		{
			sum_len += ft_lstlen(way->content) - 1;
			cur_steps = (map->ants + sum_len - 1) / ++way_q;
			if (cur_steps < map->comb.steps)
			{
				comb_number = comb_ptr->content_size;
				map->comb.quant = way_q;
				map->comb.steps = cur_steps;
				map->comb.sum_len = sum_len;
			}
			way = way->next;
		}
		comb_ptr = comb_ptr->next;
	}
	SECURE_MALLOC(map->comb.way_arr = /*(t_list**)*/ft_memalloc(sizeof(t_list*) * (map->comb.quant + 1)));
	comb_ptr = map->way;
	while (comb_ptr->content_size != comb_number)
		comb_ptr = comb_ptr->next;
	way = comb_ptr->content;
	way_q = 0;
	while (way_q < map->comb.quant)
	{
		map->comb.way_arr[way_q++] = way->content;
		way = way->next;
	}
}

void    ant_flow(t_map *map)
{
	// t_comb	*comb;
	// t_comb	comb;

	// construct_combinations(map);
	// combinations_memalloc(map);
	// print_combinations(map); // debug
	// comb = choose_combination(map);
	make_best_combination(map/*, &comb*/);
	// print_one_comb(comb, map->ants);
	print_one_comb(map);
}
