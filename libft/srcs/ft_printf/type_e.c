/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_e.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wballaba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 18:46:14 by wballaba          #+#    #+#             */
/*   Updated: 2019/05/15 13:37:08 by gabshire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

double	check_null_prec_dtoa_e(double num)
{
	if (num < 0)
		num -= 0.5;
	else
		num += 0.5;
	return (num);
}

char	*ft_dtoa_e(double num, t_specs *specs)
{
	int		ex;
	char	*val;

	ex = 0;
	if (num > 1 || num < -1)
		while (ABS(num) >= 10 && ++ex)
			num /= 10;
	else if (num == 0)
		ex = 0;
	else
		while (ABS(num) < 1 && --ex)
			num *= 10;
	val = ft_dtoa_base(num, PREC_F(specs->precision), 10);
	if (specs->flags[sharp] && !ft_strchr(val, '.'))
		val = ft_strjoin_free(val, ".", 1);
	val = ft_strjoin_free(val, "e", 1);
	val = ft_strjoin_free(val, SIGNOFEX(ex), 1);
	if (ABS(ex) >= 10)
		val = ft_strjoin_free(val, ft_itoa(ABS(ex)), 3);
	else
	{
		val = ft_strjoin_free(val, "0", 1);
		val = ft_strjoin_free(val, ft_itoa(ABS(ex)), 3);
	}
	return (val);
}

void	print_type_e(t_specs *specs, va_list *ap)
{
	char		*val;
	long double	lnbr;
	double		nbr;

	if (specs->size == L)
	{
		lnbr = va_arg(*ap, long double);
		val = use_sval(specs, ft_dtoa_e(lnbr, specs), lnbr);
	}
	else
	{
		nbr = va_arg(*ap, double);
		val = use_sval(specs, ft_dtoa_e(nbr, specs), nbr);
	}
	if (specs->type == 'E')
		val = ft_str_toupper(val);
	print_value(specs, val, ft_strlen(val));
}
