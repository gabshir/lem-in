/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillem- <jwillem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 17:38:49 by jwillem-          #+#    #+#             */
/*   Updated: 2019/05/15 18:47:15 by gabshire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	stack_has_n(char **stack, char **line)
{
	char	*ptr;

	if ((ptr = ft_strchr(*stack, '\n')))
	{
		*ptr = '\0';
		if (!(*line = ft_strdup(*stack)))
			return (-1);
		if (!(ptr = ft_strdup(ptr + 1)))
			return (-1);
		free(*stack);
		*stack = ptr;
		return (1);
	}
	return (0);
}

static int	read_line(const int fd, char **stack, char **line, char *buf)
{
	char	*tmp;
	int		rv;

	while ((rv = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[rv] = '\0';
		if (*stack)
		{
			tmp = ft_strjoin(*stack, buf);
			free(*stack);
			*stack = tmp;
		}
		else
			*stack = ft_strdup(buf);
		if (stack_has_n(stack, line))
			break ;
	}
	if (rv > 0)
		return (1);
	else
		return (rv);
}

static int	last(char **line, char **stack, int rv)
{
	if (!rv)
	{
		*line = NULL;
		if (*stack)
			free(*stack);
		*stack = NULL;
	}
	return (rv);
}

int			get_next_line(const int fd, char **line)
{
	static char	*stack[MAX_FD];
	char		*buf;
	int			rv;

	if (!line || fd < 0 || fd >= MAX_FD)
		return (-1);
	if (stack[fd])
	{
		rv = stack_has_n(&stack[fd], line);
		if (rv)
			return (rv);
	}
	if (!(buf = ft_strnew(BUFF_SIZE)))
		return (-1);
	rv = read_line(fd, &stack[fd], line, buf);
	free(buf);
	if (rv || stack[fd] == NULL || stack[fd][0] == '\0')
		return (last(line, &stack[fd], rv));
	*line = stack[fd];
	stack[fd] = NULL;
	return (1);
}
