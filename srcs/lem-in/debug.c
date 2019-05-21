/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillem- <jwillem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 21:40:57 by jwillem-          #+#    #+#             */
/*   Updated: 2019/05/21 07:48:34 by jwillem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	print_que(t_list *que)
{
	t_list		*ptr;
	static int	debug;

	ptr = que;
	ft_printf("\nWay № %d. Length = %d.\n", ++debug, ft_lstlen(que) - 1);
	while (ptr)
	{
		ft_printf("%s ", ((t_room*)ptr->content)->name);
		ptr = ptr->next;
		if (ptr)
			ft_printf("- ");
		else
			ft_printf("\n");
	}
	ft_printf("\n----------------\n");
}

void	ft_printway(t_list *obway)
{
	t_list	*listcomb;
	t_list	*comb;

	while (obway)
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
		obway = obway->next;
	}
}

void	print_path(t_path *path)
{
	int	i;

	i = -1;
	while (++i < path->len)
	{
		ft_printf("%s", path->rooms[i]->name);
		if (i + 1 < path->len)
			ft_printf(" - ");
	}
	ft_printf("\n");
}

void	print_best_comb(t_map *map)
{
	int	w_idx;
	int	sum_len;
	int	steps;

	w_idx = -1;
	sum_len = 0;
	ft_printf("\nBEST COMBINATION:\n\n");
	while (C_WAY[++w_idx].len)
	{
		sum_len += C_WAY[w_idx].len;
		steps = (map->ants + sum_len - 1) / (w_idx + 1);
		ft_printf("%d ants will be distributed to this way.\n", \
			C_WAY[w_idx].ants);
		print_path(&C_WAY[w_idx]);
		ft_printf("Length of way = %d\n", C_WAY[w_idx].len);
		ft_printf("All %d ants will be transported for %d steps.\n", \
			map->ants, steps);
		ft_printf("----------------\n\n");
	}
	ft_printf("Quantity of ways = %d\n", C_QUANT);
	ft_printf("Summary length of ways = %d\n", C_SUM_LEN);
	ft_printf("All %d ants will be transported for %d steps\n-----------\n\n", \
		map->ants, map->comb.steps);
}
