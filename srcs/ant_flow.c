/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ant_flow.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillem- <jwillem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 18:24:28 by jwillem-          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2019/05/15 15:30:06 by jwillem-         ###   ########.fr       */
=======
/*   Updated: 2019/05/15 13:37:08 by gabshire         ###   ########.fr       */
>>>>>>> master
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

// static void	make_best_combination(t_map *map)
// {
// 	t_list	*comb_ptr;
// 	t_list	*way;
// 	size_t	comb_number;
// 	int		sum_len;
// 	int		cur_steps;
// 	int		way_q;

// 	comb_ptr = map->way;
// 	C_STEPS = INT_MAX;
// 	while (comb_ptr)
// 	{
// 		way = comb_ptr->content;
// 		sum_len = 0;
// 		way_q = 0;
// 		while (way)
// 		{
// 			sum_len += ft_lstlen(way->content) - 1;
// 			cur_steps = (map->ants + sum_len - 1) / ++way_q;
// 			if (cur_steps < C_STEPS)
// 			{
// 				comb_number = comb_ptr->content_size;
// 				C_QUANT = way_q;
// 				C_STEPS = cur_steps;
// 				C_SUM_LEN = sum_len;
// 			}
// 			way = way->next;
// 		}
// 		comb_ptr = comb_ptr->next;
// 	}
// 	SECURE_MALLOC(C_WAY = ft_memalloc(sizeof(t_list*) * (C_QUANT + 1)));
// 	comb_ptr = map->way;
// 	while (comb_ptr->content_size != comb_number)
// 		comb_ptr = comb_ptr->next;
// 	way = comb_ptr->content;
// 	way_q = 0;
// 	while (way_q < C_QUANT)
// 	{
// 		C_WAY[way_q++] = way->content;
// 		way = way->next;
// 	}
// }

static void	make_best_combination(t_map *map)
{
	t_list	*comb_ptr;
	t_list	*way;
	size_t	comb_number;
	int		sum_len;
	int		cur_steps;
	int		way_q;

	comb_ptr = map->way;
	C_STEPS = INT_MAX;
	while (comb_ptr)
	{
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
		comb_ptr = comb_ptr->next;
	}
	comb_ptr = map->way;
	while (comb_ptr->content_size != comb_number)
		comb_ptr = comb_ptr->next;
	way = comb_ptr->content;
	SECURE_MALLOC(C_WAY = ft_memalloc(sizeof(t_path) * (C_QUANT + 1)));
	way_q = 0;
	while (way_q < C_QUANT)
	{
		// C_WAY[way_q++] = way->content;
		C_WAY[way_q].len = ft_lstlen(way->content) - 1;
		SECURE_MALLOC(C_WAY[way_q].rooms = ft_memalloc(sizeof(t_room*) * (C_WAY[way_q].len + 1)));
		t_list	*ptr = way->content;
		int	i = -1;
		while (ptr)
		{
			C_WAY[way_q].rooms[++i] = ptr->content;
			ptr = ptr->next;
		}
		way = way->next;
	}
}

static int	sum_difference(t_map *map, int i)
{
	static int	sum_diff;
	
	sum_diff += ft_lstlen(C_WAY[C_QUANT - 1]) - \
		ft_lstlen(C_WAY[i++]);
	if (i < C_QUANT)
		sum_difference(map, i);
	return (sum_diff);
}

static void	distribute_ants(t_map *map)
{
	int	sum_diff;
	int	min_ant;
	int	remainder;
	int	i;
	
	sum_diff = sum_difference(map, 0);
	min_ant = (map->ants - sum_diff) / C_QUANT;
	remainder = (map->ants - sum_diff) % C_QUANT;
	i = -1;
	while (++i < C_QUANT)
	{
		C_WAY[i]->content_size = min_ant + \
			ft_lstlen(C_WAY[C_QUANT - 1]) - ft_lstlen(C_WAY[i]);
		if (remainder)
		{
			C_WAY[i]->content_size++;
			remainder--;
		}
	}
}

// static t_list	*ft_lstnew_ant(void const *content, int ant)
// {
// 	t_list	*newl;

// 	if (!(newl = (t_list *)ft_memalloc(sizeof(*newl))))
// 		return (NULL);
// 	if (content == NULL)
// 	{
// 		newl->content = NULL;
// 		newl->content_size = 0;
// 	}
// 	else
// 	{
// 		newl->content = (void*)content;
// 		newl->content_size = ant;
// 	}
// 	newl->next = NULL;
// 	return (newl);
// }

// static void		let_ants_go(t_map *map)
// {
	
// }

void    ant_flow(t_map *map)
{
	make_best_combination(map);
	// print_one_comb(map);	//debug
	distribute_ants(map);
	print_one_comb(map);	//debug
	// let_ants_go(map);
}
