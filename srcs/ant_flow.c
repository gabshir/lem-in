/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ant_flow.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillem- <jwillem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 18:24:28 by jwillem-          #+#    #+#             */
/*   Updated: 2019/05/16 21:14:45 by jwillem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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
	free(number);
}

static void	show_ants_locations(t_map *map, int wi, int *cycle)
{
	static int	ant;
	int			ri;

	ri = C_WAY[wi].last_i + 1;
	while (--ri >= 0 && map->ants)
	{
		if (ri == 0 && C_WAY[wi].ants)
		{
			C_WAY[wi].rooms[ri]->ant_num = ++ant;
			C_WAY[wi].ants--;
		}
		else if (ri > 0 && C_WAY[wi].rooms[ri - 1]->ant_num)
		{
			C_WAY[wi].rooms[ri]->ant_num = C_WAY[wi].rooms[ri - 1]->ant_num;
			C_WAY[wi].rooms[ri - 1]->ant_num = 0;
		}
		else
			break ;
		print_ant(C_WAY[wi].rooms[ri]->ant_num, \
			C_WAY[wi].rooms[ri]->name, ++(*cycle));
	}
}

void		ant_flow(t_map *map)
{
	int	wi;
	int	cycle;
	
	make_best_combination(map);
	distribute_ants(map);
	wi = -1;
	cycle = -1;
	while (++wi < C_QUANT && map->ants)
	{
		show_ants_locations(map, wi, &cycle);
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
