/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillem- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/02 18:05:20 by jwillem-          #+#    #+#             */
/*   Updated: 2019/05/15 13:37:08 by gabshire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_word_quant(char const *s, char c)
{
	size_t	quant;
	size_t	i;

	i = 0;
	quant = 0;
	while (s[i])
	{
		if (s[i] == c && s[i + 1] != c)
			quant++;
		i++;
	}
	if (s[0] != '\0')
		quant++;
	return (quant);
}

static char		*ft_wordrec(const char *s, char c, size_t *i)
{
	char	*str;
	size_t	l;

	if (!(str = (char *)malloc(sizeof(char) * ft_strlen(s))))
		return (NULL);
	l = 0;
	while (s[*i] && s[*i] != c)
	{
		str[l++] = s[*i];
		*i += 1;
	}
	str[l] = '\0';
	while (s[*i] && s[*i] == c)
		*i += 1;
	return (str);
}

static void		ft_freestrsplit(char **str, size_t j)
{
	while (j > 0)
		free(str[j--]);
	free(str[j]);
	free(str);
	return ;
}

char			**ft_strsplit(char const *s, char c)
{
	char	**str;
	size_t	i;
	size_t	j;

	if (!s)
		return (NULL);
	i = 0;
	j = 0;
	if (!(str = (char **)malloc(sizeof(str) * (ft_word_quant(s, c) + 1))))
		return (NULL);
	while (s[i] && s[i] == c)
		i++;
	while (s[i] && j < ft_word_quant(s, c))
	{
		str[j] = ft_wordrec(s, c, &i);
		if (str[j] == NULL)
		{
			ft_freestrsplit(str, j - 1);
			return (NULL);
		}
		j++;
	}
	str[j] = NULL;
	return (str);
}
