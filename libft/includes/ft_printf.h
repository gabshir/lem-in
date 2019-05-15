/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillem- <jwillem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 13:57:16 by jwillem-          #+#    #+#             */
/*   Updated: 2019/05/15 13:37:08 by gabshire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# define POWER(precision)	(precision > 48 ? 48 : precision)
# define PREC_F(precision)	(precision <= -1 ? 6 : precision)
# define PREC(precision)	(precision <= -1 ? 0 : precision)
# define PREC_A(precision)	(precision <= -1 ? 13 : precision)
# define STRIFNEG(num)		(num < 0 ? "-0x" : "0x")
# define SIGNOFEX(ex)		(ex >= 0 ? "+" : "-")

# include <stdarg.h>
# include "libft.h"

int				g_len;

typedef struct	s_specs
{
	int		flags[5];
	int		width;
	int		precision;
	int		size;
	char	type;
}				t_specs;

typedef enum	e_size
{
	hh = 1,
	h,
	l,
	L,
	ll,
	j,
	z,
	t
}				t_size;

typedef enum	e_flag
{
	sharp,
	zero,
	minus,
	plus,
	space
}				t_flag;

t_specs			*create_new_specs(void);

void			find_start_specifier(char *format, va_list *ap);

char			*find_all_specifier(char *start_ptr, t_specs *specs, \
				va_list *ap);
char			*find_size_specifier(char *start_ptr, t_specs *specs);
char			*find_type_specifier(char *start_ptr, t_specs *specs);
char			*find_widht_specifier(char *start_ptr, t_specs *specs, \
				va_list *ap);
char			*find_precision_specifier(char *start_ptr, t_specs *specs, \
				va_list *ap);
char			*find_flag_specifier(char *start_ptr, t_specs *specs);

char			*get_value(char *start_ptr, t_specs *specs, va_list *ap);
void			print_value(t_specs *specs, char *val, int len_val);
char			*re_val(char *val, int *sign);
char			*use_sval(t_specs *specs, char *val, long long nbr);
char			*use_uval(t_specs *specs, char *val, unsigned long long nbr);

char			*handling_precision(t_specs *specs, char *val, int len);
char			*handling_zero(t_specs *specs, char *val, int len);
char			*handling_size(t_specs *specs, unsigned long long nb, int base);
char			*filling_zero(char *val, int len);

void			print_type_di(t_specs *specs, va_list *ap);
void			print_type_c(t_specs *specs, va_list *ap);
void			print_type_s(t_specs *specs, va_list *ap);
void			print_type_p(t_specs *specs, va_list *ap);
void			print_type_oux(t_specs *specs, va_list *ap);
void			print_type_percent(t_specs *specs);
void			print_type_f(t_specs *specs, va_list *ap);
void			print_type_e(t_specs *specs, va_list *ap);
void			print_type_a(t_specs *specs, va_list *ap);
void			print_type_g(t_specs *specs, va_list *ap);
void			print_type_n(va_list *ap);
char			*print_non_spec(char *start_ptr, t_specs *specs);

char			*ft_dtoa_base(double num, int precision, int base);
char			*ft_frac_base(double int_frac, int precision, int base);
char			*ft_dtoa_e(double num, t_specs *specs);
char			*del_last_zeros(char *val, t_specs *specs);
double			check_null_prec_dtoa_e(double num);
void			rounding(char *str, int i);

#endif
