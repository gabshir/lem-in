/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_a.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wballaba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 21:03:20 by wballaba          #+#    #+#             */
/*   Updated: 2019/04/05 12:06:09 by gabshire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*ft_frac_a(double int_frac, int precision)
{
	char	*str;
	int		i;

	i = 0;
	str = ft_strnew(precision + 1);
	while (i <= precision)
	{
		if (int_frac * 16 < 10 && int_frac * 16 >= 1)
			str[i++] = (int)(int_frac * 16) + '0';
		else if (int_frac * 16 >= 10 && int_frac * 16 >= 1)
			str[i++] = (int)(int_frac * 16) + 87;
		else
			str[i++] = '0';
		int_frac = int_frac * 16 - (int)(int_frac * 16);
	}
	if ((str[--i] > 55 && str[i] < 58) || (str[i] > 96 && str[i] < 103))
		rounding(str, --i);
	str[precision] = '\0';
	return (str);
}

static char	*ft_dtoa_a_hex(double n, double on, int ex, t_specs *specs)
{
	char				*str;
	char				*part;
	unsigned long long	int_num;
	double				int_frac;

	int_num = (unsigned long long)ABS(n);
	if (specs->precision == 0)
	{
		if (on - ft_power(2, ex) > ft_power(2, ex + 1) - on)
			int_num = 2;
		str = ft_itoa_base(int_num, 16);
	}
	else
	{
		int_frac = ABS(n) - int_num;
		part = ft_frac_a(int_frac, specs->precision);
		str = ft_uitoa_base(int_num, 16);
		str = ft_strjoin_free(str, ".", 1);
		str = ft_strjoin_free(str, part, 3);
	}
	if (specs->precision == -1 || specs->precision == 13 || \
		specs->precision == 0)
		str = del_last_zeros(str, specs);
	return (str);
}

char		*ft_dtoa_a(double num, t_specs *specs)
{
	int		ex;
	char	*val;
	double	orig_num;

	orig_num = num;
	ex = 0;
	if (num > 1 || num < -1)
		while (ABS(num) >= 2 && ++ex)
			num /= 2;
	else if (num != 0)
		while (ABS(num) < 1 && --ex)
			num *= 2;
	val = ft_dtoa_a_hex(num, orig_num, ex, specs);
	if (specs->flags[sharp] && !ft_strchr(val, '.'))
		val = ft_strjoin_free(val, ".", 1);
	val = ft_strjoin_free(val, "p", 1);
	if (ex >= 0)
		val = ft_strjoin_free(val, "+", 1);
	else
		val = ft_strjoin_free(val, "-", 1);
	val = ft_strjoin_free(val, ft_itoa(ABS(ex)), 3);
	val = ft_strjoin_free(STRIFNEG(num), val, 2);
	return (val);
}

void		put_x(char *val, double nbr)
{
	int		i;
	char	*ptr;

	i = 0;
	if (nbr < 0)
	{
		if ((ptr = ft_strchr(val + 3, 'x')))
			*ptr = '0';
		if (val[2] == '0')
			val[2] = 'x';
	}
	else
	{
		if ((ptr = ft_strchr(val + 2, 'x')))
			*ptr = '0';
		if (val[1] == '0')
			val[1] = 'x';
	}
}

void		print_type_a(t_specs *specs, va_list *ap)
{
	char		*val;
	long double	nbr;

	specs->precision = PREC_A(specs->precision);
	if (specs->size == L)
		nbr = va_arg(*ap, long double);
	else
		nbr = va_arg(*ap, double);
	val = ft_dtoa_a(nbr, specs);
	val = use_sval(specs, val, nbr);
	put_x(val, nbr);
	if (specs->type == 'A')
		val = ft_str_toupper(val);
	print_value(specs, val, ft_strlen(val));
}
