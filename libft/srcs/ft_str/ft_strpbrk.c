/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strpbrk.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wballaba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 15:40:53 by wballaba          #+#    #+#             */
/*   Updated: 2019/04/05 12:06:09 by gabshire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strpbrk(const char *s, const char *accept)
{
	size_t	lenaccept;
	size_t	i;

	lenaccept = ft_strlen((char*)accept);
	i = 0;
	if (s == NULL || accept == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		if (ft_memchr(accept, s[i], lenaccept) != NULL)
			return ((char*)s + i);
	}
	return (NULL);
}
