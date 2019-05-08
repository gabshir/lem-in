/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freelinks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabshire <gabshire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 22:31:14 by gabshire          #+#    #+#             */
/*   Updated: 2019/05/07 10:49:50 by gabshire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	ft_freedown(t_list **links, int n)
{
	t_room *read;
	t_list	*next;
	t_list	*prew;
	t_list	*temp;

	temp = *links;
	read = temp->content;
	if (read->n == n)
	{
		next = temp->next;
	//	free(temp);
		temp = NULL;
		*links = next;
		return ;
	}
	prew = temp;
	while (temp && read->n != n)
	{
		read = temp->content;
		if (read->n == n)
		{
			next = temp->next;
		//	free(temp);
			temp = NULL;
			prew->next = next;
			return ;
		}
		prew = temp;
		temp = temp->next;
	}
}