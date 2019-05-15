/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_specifier.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wballaba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 14:30:51 by wballaba          #+#    #+#             */
/*   Updated: 2019/05/15 13:37:08 by gabshire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*find_size_specifier(char *start_ptr, t_specs *specs)
{
	if (*start_ptr == 'h' && *(start_ptr + 1) == 'h' && hh > specs->size)
	{
		specs->size = hh;
		start_ptr++;
	}
	else if (*start_ptr == 'h' && *(start_ptr + 1) != 'h' && h > specs->size)
		specs->size = h;
	else if (*start_ptr == 'l' && *(start_ptr + 1) != 'l' && l > specs->size)
		specs->size = l;
	else if (*start_ptr == 'l' && *(start_ptr + 1) == 'l' && ll > specs->size)
	{
		specs->size = ll;
		start_ptr++;
	}
	else if (*start_ptr == 'L' && L > specs->size)
		specs->size = L;
	else if (*start_ptr == 'j' && j > specs->size)
		specs->size = j;
	else if (*start_ptr == 'z' && z > specs->size)
		specs->size = z;
	else if (*start_ptr == 't' && t > specs->size)
		specs->size = t;
	return (start_ptr + 1);
}

char	*find_type_specifier(char *start_ptr, t_specs *specs)
{
	if (*start_ptr == 'D')
	{
		specs->size = l;
		specs->type = 'd';
	}
	else if (*start_ptr == 'O')
	{
		specs->size = l;
		specs->type = 'o';
	}
	else if (*start_ptr == 'U')
	{
		specs->size = l;
		specs->type = 'u';
	}
	else
		specs->type = *start_ptr;
	return (start_ptr);
}

char	*find_widht_specifier(char *start_ptr, t_specs *specs, va_list *ap)
{
	if (*start_ptr == '*')
	{
		specs->width = va_arg(*ap, int);
		start_ptr++;
	}
	else
	{
		specs->width = ft_atoi(start_ptr);
		while (*start_ptr >= '0' && *start_ptr <= '9')
			start_ptr++;
	}
	if (specs->width < 0)
	{
		specs->width = ABS(specs->width);
		specs->flags[minus] = 1;
	}
	return (start_ptr);
}

char	*find_precision_specifier(char *start_ptr, t_specs *specs, va_list *ap)
{
	specs->precision = 0;
	if (*start_ptr == '*')
	{
		specs->precision = va_arg(*ap, int);
		start_ptr++;
	}
	else
	{
		specs->precision = ft_atoi(start_ptr);
		while (*start_ptr >= '0' && *start_ptr <= '9')
			start_ptr++;
	}
	return (start_ptr);
}

char	*find_flag_specifier(char *start_ptr, t_specs *specs)
{
	if (*start_ptr == '#')
		specs->flags[sharp] = 1;
	else if (*start_ptr == '0')
		specs->flags[zero] = 1;
	else if (*start_ptr == '-')
		specs->flags[minus] = 1;
	else if (*start_ptr == '+')
		specs->flags[plus] = 1;
	else if (*start_ptr == ' ')
		specs->flags[space] = 1;
	start_ptr++;
	return (start_ptr);
}
