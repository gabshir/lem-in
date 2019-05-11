/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillem- <jwillem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 21:40:57 by jwillem-          #+#    #+#             */
/*   Updated: 2019/05/11 16:38:21 by jwillem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	print_que(t_list *que)
{
	t_list	*ptr;

	ptr = que;
	while (ptr)
	{
		// ft_printf("%s(%d) ", ((t_room*)ptr->content)->name, ((t_room*)ptr->content)->cost);
		ft_printf("%s ", ((t_room*)ptr->content)->name);
		ptr = ptr->next;
		if (ptr)
			ft_printf("- ");
	}
	ft_printf("\n");
}

void	ft_printway(t_list *obway)
{
	t_list	*listcomb;
	t_list *comb;
	// t_room *read;
	// int k;

	while(obway)
	{
		listcomb = obway->content;
		// k = 0;
		ft_printf("Combination № %zu\n", obway->content_size + 1);
		while (listcomb)
		{
			comb = listcomb->content;
			print_que(comb);
			// while (comb)
			// {
			// 	read = comb->content;
			// 	ft_printf("way = %s\n", read->name);
			// 	comb = comb->next;
			// }
			// k++;
			listcomb = listcomb->next;
		}
		ft_printf("------------------------------\n");
		// ft_printf("kol way %d\n", k);
		obway = obway->next;
	}
}

// void	print_ways(t_list *ways)
// {
// 	t_list	*way;
// 	int		i;
// 	// size_t	comb;
// 	// size_t	paths_q;

// 	way = ways;
// 	i = 0;
// 	// comb = 1;
// 	while (way)
// 	{
// 		ft_printf("Way № %d: ", ++i);
// 		print_que(way->content);
// 		way = way->next;
// 	}
// }

void	print_one_comb(t_comb *comb, int ants)
{
	int	w_idx;
	
	w_idx = 0;
	ft_printf("BEST COMBINATION:\n");
	while (comb->way_arr[w_idx])
		print_que(comb->way_arr[w_idx++]);
	ft_printf("\nQuantity of ways = %d\n", comb->quant);
	ft_printf("Summary length of ways = %d\n", comb->sum_len);
	ft_printf("All %d ants will be transported for %d steps\n------------------\n\n", \
		ants, comb->steps);
}

void	print_combinations(t_map *map)
{
	int	i;
	int	w_idx;

	i = -1;
	while (map->comb[++i].way_arr)
	{
		ft_printf("Combination № %d:\n\n", i + 1);
		w_idx = 0;
		while (map->comb[i].way_arr[w_idx])
			print_que(map->comb[i].way_arr[w_idx++]);
		ft_printf("\nQuantity of ways = %d\n", map->comb[i].quant);
		ft_printf("Summary length of ways = %d\n", map->comb[i].sum_len);
		ft_printf("All %d ants will be transported for %d steps\n------------------\n\n", \
			map->ants, map->comb[i].steps);
	}
}
