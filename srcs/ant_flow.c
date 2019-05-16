/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ant_flow.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillem- <jwillem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 18:24:28 by jwillem-          #+#    #+#             */
/*   Updated: 2019/05/16 17:12:44 by jwillem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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
	way_q = -1;
	while (++way_q < C_QUANT)
	{
		C_WAY[way_q].len = ft_lstlen(way->content) - 1;
		SECURE_MALLOC(C_WAY[way_q].rooms = ft_memalloc(sizeof(t_room*) * (C_WAY[way_q].len + 1)));
		t_list	*ptr = way->content;
		int	i = -1;
		while (ptr->next)
		{
			C_WAY[way_q].rooms[++i] = ptr->next->content;
			ptr = ptr->next;
		}
		way = way->next;
	}
}

static int	sum_difference(t_map *map, int i)
{
	static int	sum_diff;
	
	sum_diff += C_WAY[C_QUANT - 1].len - C_WAY[i++].len;
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
		C_WAY[i].ants = min_ant + C_WAY[C_QUANT - 1].len - C_WAY[i].len;
		C_WAY[i].last_i = 0;
		if (remainder)
		{
			C_WAY[i].ants++;
			remainder--;
		}
	}
}

static void	print_ant(int ant, char *room, int cycle)
{
	char	*number;
	
	if (cycle > 0)
		write(1, " ", 1);
	write(1, "L", 1);
	number = ft_itoa(ant);
	ft_putstr(number);
	write(1, "-", 1);
	ft_putstr(room);
	// write(1, " ", 1);
	free(number);
}

static void	let_ants_go(t_map *map)
{
	int	ant;
	int	wi;
	int	ri;
	int	cycle;
	
	ant = 1;
	wi = -1;
	cycle = -1;
	while (++wi < C_QUANT && map->ants)
	{
		
		ri = C_WAY[wi].last_i + 1;
		while (--ri >= 0 && map->ants)
		{
			if (ri == 0 && C_WAY[wi].ants)
			{
				C_WAY[wi].rooms[ri]->ant_num = ant++;
				C_WAY[wi].ants--;
			}
			else if (ri > 0 && C_WAY[wi].rooms[ri - 1]->ant_num)
			{
				C_WAY[wi].rooms[ri]->ant_num = C_WAY[wi].rooms[ri - 1]->ant_num;
				C_WAY[wi].rooms[ri - 1]->ant_num = 0;
			}
			else
				break ;
			print_ant(C_WAY[wi].rooms[ri]->ant_num, C_WAY[wi].rooms[ri]->name, ++cycle);
		}
		if (C_WAY[wi].last_i < C_WAY[wi].len - 1)
			C_WAY[wi].last_i++;
		else
			map->ants--;
		if (wi == C_QUANT - 1 || !map->ants)
		{
			wi = -1;
			cycle = -1;
			write(1, "\n", 1);
		}
	}
}

void    ant_flow(t_map *map)
{
	make_best_combination(map);
	// print_one_comb(map);	//debug
	distribute_ants(map);
	// print_best_comb(map);	//debug
	let_ants_go(map);
}
