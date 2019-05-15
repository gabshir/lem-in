/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_struct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wballaba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 22:25:20 by wballaba          #+#    #+#             */
/*   Updated: 2019/05/15 13:37:08 by gabshire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_specs	*create_new_specs(void)
{
	t_specs	*specs;
	int		i;

	i = -1;
	if (!(specs = (t_specs *)malloc(sizeof(t_specs))))
		return (NULL);
	while (++i < 5)
		specs->flags[i] = 0;
	specs->type = 0;
	specs->width = 0;
	specs->precision = -1;
	specs->size = 0;
	return (specs);
}
