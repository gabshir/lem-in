/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillem- <jwillem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 14:36:10 by gabshire          #+#    #+#             */
/*   Updated: 2019/05/12 20:59:31 by jwillem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*get_correct_file(t_list **file, int fd)
{
	t_list	*tmp;

	tmp = *file;
	while (tmp)
	{
		if ((int)tmp->content_size == fd)
			return (tmp);
		tmp = tmp->next;
	}
	if (!(tmp = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	tmp->content = NULL;
	tmp->content = ft_strnew(1);
	tmp->content_size = (size_t)fd;
	ft_lstadd(file, tmp);
	tmp->next = NULL;
	return (tmp);
}

static int		ft_poisk(const char *str, char c)
{
	int		i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

static char		*ft_strjoin_freep(char *str1, char *str2)
{
	char	*s;

	s = ft_strjoin(str1, str2);
	free(str1);
	str1 = NULL;
	return (s);
}

static int		last(t_get *n, char **line)
{
	*line = ft_strnew(1);
	free(n->temp->content);
	free(n->temp);
	return (0);
}

int				get_next_line(const int fd, char **line)
{
	t_get			n;
	static t_list	*bufer;
	char			buf[BUFF_SIZE + 1];

	if (fd < 0 || BUFF_SIZE < 0 || !line || read(fd, buf, 0) == -1)
		return (-1);
	n.temp = get_correct_file(&bufer, fd);
	while ((n.o = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[n.o] = '\0';
		n.temp->content = ft_strjoin_freep(n.temp->content, buf);
		if (ft_poisk(buf, '\n') != n.o)
			break ;
	}
	if (n.o < BUFF_SIZE && ft_strlen(bufer->content) == 0)
		return (last(&n, line));
	n.o = ft_poisk(n.temp->content, '\n');
	*line = ft_strsub(n.temp->content, 0, n.o);
	n.s = ft_strsub(n.temp->content, n.o + 1, ft_strlen(n.temp->content) - n.o);
	free(n.temp->content);
	n.temp->content = n.s;
	return (1);
}
