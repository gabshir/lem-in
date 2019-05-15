/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_g.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wballaba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 20:56:25 by wballaba          #+#    #+#             */
/*   Updated: 2019/05/15 13:37:08 by gabshire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*del_last_zeros(char *val, t_specs *specs)
{
	char	*str;
	size_t	i;

	if (!ft_strchr(val, '.'))
		return (val);
	if (!(str = ft_strdup(val)))
		return (NULL);
	i = 0;
	while (str[i] != '\0' && str[i] != 'p')
		i++;
	while (str[--i] == '0')
		str[i] = '\0';
	if (!specs->flags[sharp] && str[i] == '.')
		str[i] = '\0';
	free(val);
	return (str);
}

static char	*for_val_zero_int(t_specs *specs, long double nbr)
{
	char		*val;

	if (specs->precision == 0)
		specs->precision = 1;
	val = ft_dtoa_base(nbr, specs->precision, 10);
	if (!specs->flags[sharp])
		val = del_last_zeros(val, specs);
	if (specs->flags[sharp] && !ft_strchr(val, '.'))
		val = ft_strjoin_free(val, ".", 1);
	val = use_sval(specs, val, nbr);
	return (val);
}

static char	*for_val_one_int(t_specs *specs, long double nbr, int int_len)
{
	char		*val;

	if (specs->precision > 0)
		specs->precision = specs->precision - int_len;
	val = ft_dtoa_base(nbr, specs->precision, 10);
	if (!specs->flags[sharp])
		val = del_last_zeros(val, specs);
	if (specs->flags[sharp] && !ft_strchr(val, '.'))
		val = ft_strjoin_free(val, ".", 1);
	val = use_sval(specs, val, nbr);
	return (val);
}

static char	*for_type_e_in_type_g(t_specs *specs, long double nbr)
{
	char		*val;

	if (specs->precision > 0)
		specs->precision--;
	val = ft_dtoa_e(nbr, specs);
	val = del_last_zeros(val, specs);
	val = use_sval(specs, val, nbr);
	return (val);
}

void		print_type_g(t_specs *specs, va_list *ap)
{
	char		*val;
	long double	nbr;
	int			int_len;

	if (specs->size == L)
		nbr = va_arg(*ap, long double);
	else
		nbr = va_arg(*ap, double);
	specs->precision = PREC_F(specs->precision);
	int_len = ft_intlen(nbr);
	if (specs->precision == 0 && ABS(nbr) >= 1)
		nbr = check_null_prec_dtoa_e(nbr);
	if (ABS(nbr) < 1)
		val = for_val_zero_int(specs, nbr);
	else if (specs->precision >= int_len ||
		(specs->precision == 0 && ABS(nbr) < 10))
		val = for_val_one_int(specs, nbr, int_len);
	else
		val = for_type_e_in_type_g(specs, nbr);
	if (specs->type == 'G')
		val = ft_str_toupper(val);
	print_value(specs, val, ft_strlen(val));
}
