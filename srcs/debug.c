/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillem- <jwillem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 21:40:57 by jwillem-          #+#    #+#             */
/*   Updated: 2019/05/13 17:06:16 by gabshire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	print_que(t_list *que)
{
	t_list	*ptr;
	static int	debug;

	ptr = que;
	ft_printf("\nWay № %d. Length = %d.\n", ++debug, ft_lstlen(que) - 1);
	// while (ptr)
	// {
	// 	ft_printf("%s ", ((t_room*)ptr->content)->name);
	// 	ptr = ptr->next;
	// 	if (ptr)
	// 		ft_printf("- ");
	// 	else
	// 		ft_printf("\n");
	// }
	// ft_printf("\n----------------\n");
}

void	ft_printway(t_list *obway)
{
	t_list	*listcomb;
	t_list *comb;

	while(obway)
	{
		listcomb = obway->content;
		ft_printf("Combination № %zu\n", obway->content_size + 1);
		while (listcomb)
		{
			comb = listcomb->content;
			print_que(comb);
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

void	print_one_comb(t_map *map)
{
	int	w_idx;
	int	sum_len;
	int	steps;
	
	w_idx = 0;
	sum_len = 0;
	ft_printf("BEST COMBINATION:\n");
	while (C_WAY[w_idx])
	{
		sum_len += ft_lstlen(C_WAY[w_idx]) - 1;
		steps = (map->ants + sum_len - 1) / (w_idx + 1);
		ft_printf("%d ants will be distributed to this way.\n", C_WAY[w_idx]->content_size);
		print_que(C_WAY[w_idx++]);
		ft_printf("All %d ants will be transported for %d steps.\n", \
			map->ants, steps);
		ft_printf("----------------\n");
	}
	ft_printf("\nQuantity of ways = %d\n", C_QUANT);
	ft_printf("Summary length of ways = %d\n", C_SUM_LEN);
	ft_printf("All %d ants will be transported for %d steps\n------------------\n\n", \
		map->ants, map->comb.steps);
}
