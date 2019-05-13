/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_power.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillem- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 18:33:27 by jwillem-          #+#    #+#             */
/*   Updated: 2019/05/13 17:06:16 by gabshire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_power(double num, int power)
{
	int		count;
	double	number;

	number = 1;
	count = 1;
	if (power == 0)
		return (1);
	else
	{
		while (count++ <= ABS(power))
			if (power < 0)
				number = number / num;
			else if (power > 0)
				number *= num;
	}
	return (number);
}
