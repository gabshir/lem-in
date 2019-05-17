/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillem- <jwillem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 16:03:52 by jwillem-          #+#    #+#             */
/*   Updated: 2019/05/17 13:17:33 by gabshire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "lem_in.h"

int    memory_error(void)
{
    ft_printf(ER "Couldn't allocate memory.\n");
	exit(1);
    return (1);
}

void	error_create_links(char *str)
{
	ft_printf(ER "Room %s is not found.\n", str);
	exit(1);
}