/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wballaba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 17:04:59 by wballaba          #+#    #+#             */
/*   Updated: 2019/04/05 12:06:09 by gabshire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_read_file(char *filename)
{
	int fd;

	if ((fd = open(filename, O_RDONLY)) == -1)
	{
		ft_putstr("Error: could not open file \"");
		ft_putstr(filename);
		ft_putstr("\".\n");
	}
	return (fd);
}
