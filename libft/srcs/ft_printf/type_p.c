/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_p.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillem- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 19:12:32 by jwillem-          #+#    #+#             */
/*   Updated: 2019/05/15 13:37:08 by gabshire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_type_p(t_specs *specs, va_list *ap)
{
	char				*val;
	unsigned long long	nbr;
	int					len;

	nbr = (unsigned long long)va_arg(*ap, void *);
	if (nbr == 0 && !specs->precision)
		val = ft_strnew(1);
	else
	{
		val = ft_uitoa_base(nbr, 16);
		len = ft_strlen(val);
		if (specs->precision || specs->flags[minus])
			specs->flags[zero] = 0;
		if (specs->precision - len > 0)
			val = filling_zero(val, specs->precision - len);
		len = ft_strlen(val);
		if (specs->flags[zero] && (specs->width - len - 2) > 0)
			val = filling_zero(val, specs->width - len + 2);
	}
	val = ft_strjoin_free("0x", val, 2);
	len = ft_strlen(val);
	print_value(specs, val, len);
}
