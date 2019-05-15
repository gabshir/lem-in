/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_s.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wballaba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 15:34:18 by wballaba          #+#    #+#             */
/*   Updated: 2019/05/15 13:37:08 by gabshire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_type_s(t_specs *specs, va_list *ap)
{
	char	*val;
	char	*tmp_str;
	int		len;

	if (specs->size == l)
	{
		val = ft_strdup(va_arg(*ap, char *));
	}
	else
		val = ft_strdup(va_arg(*ap, char *));
	if (val == NULL)
		val = ft_strdup("(null)");
	if (specs->precision >= 0)
	{
		tmp_str = ft_strnew(specs->precision);
		val = ft_strncat(tmp_str, val, specs->precision);
	}
	len = ft_strlen(val);
	if (specs->flags[zero] && !specs->flags[minus])
		val = filling_zero(val, specs->width - len);
	else if (specs->flags[zero] && specs->flags[minus])
		specs->flags[zero] = 0;
	len = ft_strlen(val);
	print_value(specs, val, len);
}
