/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_c.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wballaba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 15:34:11 by wballaba          #+#    #+#             */
/*   Updated: 2019/05/13 17:06:16 by gabshire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_type_c(t_specs *specs, va_list *ap)
{
	char	*val;
	int		len;

	val = ft_strnew(1);
	specs->precision = PREC(specs->precision);
	if (specs->size == l)
	{
		val[0] = va_arg(*ap, int);
		val[0] = (wchar_t)val[0];
	}
	else
	{
		val[0] = va_arg(*ap, int);
		val[0] = (char)val[0];
	}
	if (specs->flags[zero] && !specs->flags[minus])
		val = filling_zero(val, specs->width - 1);
	else if (specs->flags[zero] && specs->flags[minus])
		specs->flags[zero] = 0;
	len = ft_strlen(val);
	if (len == 0)
		len++;
	print_value(specs, val, len);
}
