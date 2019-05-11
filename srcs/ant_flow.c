/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ant_flow.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillem- <jwillem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 18:24:28 by jwillem-          #+#    #+#             */
/*   Updated: 2019/05/11 20:50:46 by jwillem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

// static void fill_combinations(t_map *map)
// {
// 	t_list  *way;
// 	t_list  *ptr;
// 	int     i;
// 	int     len;
// 	int		w_idx;

// 	way = map->way;
// 	i = -1;
// 	while (way)
// 	{
// 		// ft_printf("Current content_size = %d\n", way->content_size);
// 		if (i < (int)way->content_size)
// 		{
// 			if (i >= 0)
// 				map->comb[i].steps = (map->ants + map->comb[i].sum_len - 1) / map->comb[i].quant;
// 		    i++;
// 			len = 0;
// 			w_idx = 0;
// 			ptr = way;
// 			while (ptr && (int)ptr->content_size == i)
// 			{
// 				ptr = ptr->next;
// 				len++;
// 			}
// 			if (!(map->comb[i].way_arr = (t_list**)ft_memalloc(sizeof(t_list*) * (len + 1))))
// 			{
// 				ft_printf(ER "Couldn't allocate memory.\n");
// 				exit(1);
// 			}
// 			map->comb[i].quant = len;
// 		}
// 		map->comb[i].sum_len += ft_lstlen(way->content) - 1;
// 		map->comb[i].way_arr[w_idx++] = way->content;
// 		// print_que(map->comb[i].way_arr[w_idx++]);
//         // w_idx++;
// 		way = way->next;
// 	}
// 	map->comb[i].steps = (map->ants + map->comb[i].sum_len - 1) / map->comb[i].quant;
// }

// static void combinations_memalloc(t_map *map)
// {
// 	t_list  *way;
// 	int     mem;
// 	int     i;

// 	way = map->way;
// 	while (way->next)
// 		way = way->next;
//     // ft_printf("Quantity of combinations = %d\n", way->content_size + 1);
//     mem = way->content_size + 2;
// 	if (!(map->comb = (t_comb*)ft_memalloc(sizeof(t_comb) * mem)))
// 	{
// 		ft_printf(ER "Couldn't allocate memory.\n");
// 		exit(1);
// 	}
// 	i = -1;
// 	while (++i < mem - 2)
// 	// {
// 		// map->comb[i].quant = 0;
// 		map->comb[i].sum_len = 0;
// 	// 	map->comb[i].way_arr = NULL;
// 	// }
// 	fill_combinations(map);
// }

static void	combinations_memalloc(t_map *map)
{
	int		mem;
	int		i;
	int		w_idx;
	t_list	*comb;
	t_list	*path;

	mem = ft_lstlen(map->way) + 1;
	SECURE_MALLOC(map->comb = (t_comb*)ft_memalloc(sizeof(t_comb) * mem));
	i = -1;
	comb = map->way;
	while (++i < mem - 1 && comb)
	{
		path = comb->content;
		map->comb[i].quant = ft_lstlen(path);
		map->comb[i].sum_len = 0;
		SECURE_MALLOC(map->comb[i].way_arr = (t_list**)ft_memalloc(sizeof(t_list*) * (map->comb[i].quant + 1)));
		w_idx = 0;
		while (path)
		{
			map->comb[i].sum_len += ft_lstlen(path->content) - 1;
			map->comb[i].way_arr[w_idx++] = path->content;
			path = path->next;
		}
		map->comb[i].steps = (map->ants + map->comb[i].sum_len - 1) / map->comb[i].quant;
		comb = comb->next;
	}
}

static t_comb	*choose_combination(t_map *map)
{
	t_comb	*comb;
	int	i;
	int	min;
	
	i = -1;
	min = INT_MAX;
	// comb = &map->comb[i];
	while (map->comb[++i].steps)
	{
		if (map->comb[i].steps < min)
		{
			min = map->comb[i].steps;
			comb = &map->comb[i];
		}
	}
	return (comb);
}

void    ant_flow(t_map *map)
{
	t_comb	*comb;

	// construct_combinations(map);
	combinations_memalloc(map);
	// print_combinations(map); // debug
	comb = choose_combination(map);
	print_one_comb(comb, map->ants);
}
