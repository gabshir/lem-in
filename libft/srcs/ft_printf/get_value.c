/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_value.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wballaba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 17:24:05 by wballaba          #+#    #+#             */
/*   Updated: 2019/05/13 17:06:17 by gabshire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	get_bonus_value(t_specs *specs, va_list *ap)
{
	if (specs->type == 'f' || specs->type == 'F')
		print_type_f(specs, ap);
	else if (specs->type == 'e' || specs->type == 'E')
		print_type_e(specs, ap);
	else if (specs->type == 'a' || specs->type == 'A')
		print_type_a(specs, ap);
	else if (specs->type == 'g' || specs->type == 'G')
		print_type_g(specs, ap);
	else if (specs->type == 'n')
		print_type_n(ap);
}

char	*get_value(char *start_ptr, t_specs *specs, va_list *ap)
{
	if (specs->type == 'd' || specs->type == 'i')
		print_type_di(specs, ap);
	else if (specs->type == 'c')
		print_type_c(specs, ap);
	else if (specs->type == 'p')
		print_type_p(specs, ap);
	else if (specs->type == 's')
		print_type_s(specs, ap);
	else if (specs->type == 'o' || specs->type == 'u' || specs->type == 'x'
		|| specs->type == 'X' || specs->type == 'b')
		print_type_oux(specs, ap);
	else if (specs->type == '%')
		print_type_percent(specs);
	else if (specs->type == 'f' || specs->type == 'F' || specs->type == 'e' ||
			specs->type == 'E' || specs->type == 'a' || specs->type == 'A' ||
			specs->type == 'g' || specs->type == 'G' || specs->type == 'n')
		get_bonus_value(specs, ap);
	else
		start_ptr = print_non_spec(start_ptr, specs);
	return (start_ptr);
}

void	print_value(t_specs *specs, char *val, int len_val)
{
	char *tmp_str;

	if (specs->width > len_val)
	{
		tmp_str = ft_strnew(specs->width - len_val);
		ft_memset(tmp_str, ' ', specs->width - len_val);
		if (specs->flags[minus])
			val = ft_strjoin_free(val, tmp_str, 3);
		else
			val = ft_strjoin_free(tmp_str, val, 3);
		g_len += specs->width;
		write(1, val, specs->width);
		free(val);
		return ;
	}
	else
		write(1, val, len_val);
	free(val);
	g_len += len_val;
}
