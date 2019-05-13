/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillem- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 14:04:39 by jwillem-          #+#    #+#             */
/*   Updated: 2019/05/13 17:06:16 by gabshire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_get_int_len(long num)
{
	size_t	len;

	len = 0;
	if (num <= 0)
	{
		len++;
		num = num * -1;
	}
	while (num > 0)
	{
		len++;
		num = num / 10;
	}
	return (len);
}

char			*ft_itoa(int n)
{
	size_t	len;
	char	*str;
	long	num;

	num = n;
	len = ft_get_int_len(num);
	if (!(str = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	str[len--] = '\0';
	if (n == 0)
		str[0] = '0';
	if (n < 0)
	{
		str[0] = '-';
		num *= -1;
	}
	while (num > 0)
	{
		str[len--] = num % 10 + '0';
		num /= 10;
	}
	return (str);
}
