/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_n.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillem- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 16:59:47 by jwillem-          #+#    #+#             */
/*   Updated: 2019/05/15 13:37:08 by gabshire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_type_n(va_list *ap)
{
	size_t	*p;

	p = va_arg(*ap, size_t *);
	*p = g_len;
}
