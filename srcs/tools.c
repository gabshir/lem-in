/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillem- <jwillem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 04:44:02 by jwillem-          #+#    #+#             */
/*   Updated: 2019/05/11 14:46:28 by jwillem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

// int		links_quantity(t_room *room)
// {
// 	int		i;
// 	t_list	*ptr;

// 	i = 0;
// 	if (room)
// 	{
// 		ptr = room->links;
// 		while (ptr)
// 		{
// 			ptr = ptr->next;
// 			i++;
// 		}
// 	}
// 	return (i);
// }

int		check_existing_links(t_list *links, char *r_name)
{
	t_list	*ptr;

	ptr = links;
	while (ptr)
	{
		if (!(ft_strcmp(((t_room*)ptr->content)->name, r_name)))
			return (1);
		ptr = ptr->next;
	}
	return (0);
}
