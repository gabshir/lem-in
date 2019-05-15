/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_non.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wballaba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 17:59:20 by wballaba          #+#    #+#             */
/*   Updated: 2019/05/15 13:37:08 by gabshire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*print_non_spec(char *start_ptr, t_specs *specs)
{
	char	*val;

	val = ft_strnew(1);
	val[0] = specs->type;
	print_value(specs, val, 1);
	start_ptr++;
	return (start_ptr);
}
