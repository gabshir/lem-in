/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freelinks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabshire <gabshire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 22:31:14 by gabshire          #+#    #+#             */
/*   Updated: 2019/05/13 18:05:46 by gabshire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	freefist(t_list **links)
{
	t_list *next;

	next = links[0]->next;
	free(links[0]);
	links[0] = NULL;
	*links = next;
}

static void	freeob(t_list **links, int n)
{
	t_room *read;
	t_list	*next;
	t_list	*prew;
	t_list	*temp;

	temp = *links;
	prew = temp;
	read = temp->content;
	while (temp && read->n != n)
	{
		read = temp->content;
		if (read->n == n)
		{
			next = temp->next;
			free(temp);
			temp = NULL;
			prew->next = next;
			return ;
		}
		prew = temp;
		temp = temp->next;
	}
}

void	ft_freedown(t_list **links, int n)
{
	t_room *read;
	t_list	*temp;

	temp = *links;
	read = temp->content;
	if (read->n == n)
	{
		freefist(links);
		return ;
	}
	freeob(links, n);

}