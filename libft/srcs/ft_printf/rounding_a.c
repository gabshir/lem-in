/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rounding_a.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillem- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 15:53:23 by jwillem-          #+#    #+#             */
/*   Updated: 2019/04/05 12:06:09 by gabshire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	int_one_char(char *str)
{
	char	c;
	int		a;

	c = *str;
	a = ft_atoi(&c);
	return (a);
}

void		rounding(char *str, int i)
{
	if (str[i] != 'f' && str[i] != '9' && (str[i + 1] != '8' || i == 0))
		str[i] += 1;
	else if (str[i + 1] == '8')
	{
		if ((str[i] > '0' && str[i] < '9' && int_one_char(&str[i]) % 2 \
			&& str[i] != '3') || str[i] == 'b' || str[i] == 'd')
			str[i] = str[i] + 1;
		else if (str[i] == '0' || str[i] == 'f')
			str[i] = '0';
	}
	else if (str[i] == 'f')
	{
		str[i] = '0';
		rounding(str, --i);
	}
	else if (str[i] == '9')
		str[i] = 'a';
}
