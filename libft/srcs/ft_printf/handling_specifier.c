/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_specifier.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wballaba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 15:10:14 by wballaba          #+#    #+#             */
/*   Updated: 2019/05/13 17:06:17 by gabshire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*re_val(char *val, int *sign)
{
	char *res;

	if (val[0] == '-')
	{
		(*sign) = -1;
		val++;
		res = ft_strnew(ft_strlen(val));
		res = ft_strcpy(res, val);
		return (res);
	}
	return (val);
}

char	*filling_zero(char *val, int len)
{
	char	*tmp_str;

	tmp_str = ft_strnew(len);
	ft_memset(tmp_str, '0', len);
	val = ft_strjoin_free(tmp_str, val, 3);
	return (val);
}

/*
** функции используются для спецификаторов difF
*/

char	*use_sval(t_specs *specs, char *val, long long nbr)
{
	int		len;
	int		sign;

	sign = 0;
	if (nbr == 0 && specs->precision == 0 && specs->type != 'a'
		&& specs->type != 'A' && specs->type != 'e' && specs->type != 'g')
		return (NULL);
	val = re_val(val, &sign);
	len = ft_strlen(val);
	if ((sign == -1 || specs->flags[plus] || specs->flags[space]) &&
		((specs->precision < 0 && specs->type == 'd') || specs->type != 'd'))
		len++;
	if ((specs->flags[minus] || specs->precision >= 0) && specs->type == 'd')
		specs->flags[zero] = 0;
	if (specs->precision > len && specs->type == 'd')
		val = filling_zero(val, specs->precision - len);
	else if (specs->flags[zero] && specs->width > len)
		val = filling_zero(val, specs->width - len);
	if (sign < 0)
		val = ft_strjoin_free("-", val, 2);
	else if (specs->flags[plus] && sign >= 0)
		val = ft_strjoin_free("+", val, 2);
	else if (specs->flags[space] && !specs->flags[plus] && sign >= 0)
		val = ft_strjoin_free(" ", val, 2);
	return (val);
}

/*
** функции используются для спецификаторов ouxX
*/

char	*use_uval(t_specs *specs, char *val, unsigned long long nbr)
{
	int		len;

	len = ft_strlen(val);
	if (nbr == 0 && specs->precision == 0)
		return (NULL);
	if (specs->precision > 0 || specs->flags[minus])
		specs->flags[zero] = 0;
	if (specs->flags[sharp] && specs->precision < 0 && nbr)
	{
		if (specs->type == 'x' || specs->type == 'X')
			len += 2;
		else if (specs->type == 'o')
			len++;
	}
	if (specs->precision && specs->precision >= len)
		val = filling_zero(val, specs->precision - len);
	if (specs->flags[zero] && (specs->width - len) > 0)
		val = filling_zero(val, specs->width - len);
	return (val);
}
