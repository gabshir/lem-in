/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillem- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 05:41:25 by jwillem-          #+#    #+#             */
/*   Updated: 2019/05/13 17:06:16 by gabshire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long double	ft_numscroll(const char *str, size_t i, long double num, int sign)
{
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			num = (num * 10) + (str[i] - '0');
			i++;
		}
		else
			break ;
		if (num >= 9223372036854775807 && sign == 1)
			return (num = -1);
		else if (num > 9223372036854775807 && sign == -1)
			return (num = 0);
	}
	while ((num > 2147483648 && num <= 9223372036854775807) && sign == -1)
		num = num - 4294967296;
	while ((num > 2147483647 && num < 9223372036854775807) && sign == 1)
		num = num - 4294967296;
	return (num);
}

int			ft_atoi(const char *str)
{
	size_t		i;
	int			sign;
	long double num;
	int			res;

	i = 0;
	num = 0;
	sign = 1;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\v' \
			|| str[i] == '\r' || str[i] == '\n' || str[i] == '\f')
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	num = ft_numscroll(str, i, num, sign);
	num *= sign;
	res = (int)num;
	return (res);
}
