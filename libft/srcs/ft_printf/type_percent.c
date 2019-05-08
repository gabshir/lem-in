/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_percent.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wballaba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/12 22:40:36 by wballaba          #+#    #+#             */
/*   Updated: 2019/04/05 12:06:09 by gabshire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_type_percent(t_specs *specs)
{
	char *val;

	val = ft_strnew(1);
	val[0] = '%';
	if (specs->flags[zero] && !specs->flags[minus]
		&& specs->width > 1)
		val = filling_zero(val, specs->width - 1);
	print_value(specs, val, ft_strlen(val));
}
