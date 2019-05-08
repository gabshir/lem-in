/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillem- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 20:48:37 by jwillem-          #+#    #+#             */
/*   Updated: 2019/04/05 12:06:09 by gabshire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	ft_unsllonglen(unsigned long long num, int base)
{
	size_t	i;

	i = 0;
	if (num == 0)
		return (i = 1);
	while (num)
	{
		i++;
		num /= base;
	}
	return (i);
}

char			*ft_uitoa_base(unsigned long long num, int base)
{
	char	*str;
	size_t	digits;

	digits = ft_unsllonglen(num, base);
	str = ft_strnew(digits);
	while (digits-- > 0)
	{
		if (num % base < 10)
			str[digits] = num % base + '0';
		else
			str[digits] = num % base + 87;
		num /= base;
	}
	return (str);
}
