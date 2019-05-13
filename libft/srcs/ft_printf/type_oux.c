/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_oux.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillem- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/12 15:03:03 by jwillem-          #+#    #+#             */
/*   Updated: 2019/05/13 17:06:17 by gabshire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*handling_size(t_specs *specs, unsigned long long nb, int base)
{
	char	*val;

	if (specs->size == hh)
		val = use_uval(specs, ft_uitoa_base((unsigned char)nb, base), nb);
	else if (specs->size == h)
		val = use_uval(specs, ft_uitoa_base((unsigned short int)nb, base), nb);
	else if (specs->size == l)
		val = use_uval(specs, ft_uitoa_base((unsigned long long)nb, base), nb);
	else if (specs->size == ll)
		val = use_uval(specs, ft_uitoa_base((unsigned long long)nb, base), nb);
	else if (specs->size == j)
		val = use_uval(specs, ft_uitoa_base((uintmax_t)nb, base), nb);
	else if (specs->size == z)
		val = use_uval(specs, ft_uitoa_base((size_t)nb, base), nb);
	else if (specs->size == t)
		val = use_uval(specs, ft_uitoa_base((uintptr_t)nb, base), nb);
	else
		val = use_uval(specs, ft_uitoa_base((unsigned int)nb, base), nb);
	return (val);
}

void	print_type_oux(t_specs *specs, va_list *ap)
{
	unsigned long long	nbr;
	char				*val;

	nbr = va_arg(*ap, unsigned long long);
	if (specs->flags[minus])
		specs->flags[zero] = 0;
	if (specs->type == 'o')
		val = handling_size(specs, nbr, 8);
	else if (specs->type == 'u')
		val = handling_size(specs, nbr, 10);
	else if (specs->type == 'b')
		val = handling_size(specs, nbr, 2);
	else if (specs->type == 'x' || specs->type == 'X')
		val = handling_size(specs, nbr, 16);
	if (specs->flags[sharp])
	{
		if ((specs->type == 'x' || specs->type == 'X') && nbr)
			val = ft_strjoin_free("0x", val, 2);
		else if (specs->type == 'o' && specs->precision <= 0
			&& (nbr != 0 || !specs->precision))
			val = ft_strjoin_free("0", val, 2);
	}
	if (specs->type == 'X')
		val = ft_str_toupper(val);
	print_value(specs, val, ft_strlen(val));
}
