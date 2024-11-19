/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilbert <igilbert@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 10:18:06 by igilbert          #+#    #+#             */
/*   Updated: 2024/11/19 12:52:42 by igilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	full_read(char **buffer, int *p, int fd)
{
	char	*tmp;
	int		i;

	tmp = ft_realloc(*buffer, *p, *p + BUFFER_SIZE);
	if (!tmp)
	{
		free(*buffer);
		*buffer = NULL;
		*p = 0;
		return (-1);
	}
	*buffer = tmp;
	i = read(fd, *buffer + *p, BUFFER_SIZE);
	if (i < 0)
	{
		free(*buffer);
		*buffer = NULL;
		*p = 0;
		return (-1);
	}
	if (i > 0)
		*p += i;
	(*buffer)[*p] = '\0';
	return (i);
}

int	get_line(char *buffer, int p)
{
	int	i;

	i = 0;
	while (i < p)
	{
		if (buffer[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

int	ext_line(char **buffer, int *p, char **line)
{
	char	*line_tmp;
	char	*tmp;
	int		i;

	i = get_line(*buffer, *p);
	if (i == -1)
		return (0);
	line_tmp = ft_substr(*buffer, 0, i + 1);
	tmp = ft_substr(*buffer, i + 1, *p - i - 1);
	if (*buffer)
		free(*buffer);
	*buffer = tmp;
	*p = *p - i - 1;
	*line = line_tmp;
	return (1);
}

char	*free_buffer(char **buffer)
{
	if (*buffer)
	{
		free(*buffer);
		*buffer = NULL;
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	static int	p;
	char		*line;
	int			i;

	if (fd < 0)
		return (free_buffer(&buffer));
	if (ext_line(&buffer, &p, &line) == 1)
		return (line);
	while (1)
	{
		i = full_read(&buffer, &p, fd);
		if (i == -1 || (i == 0 && p == 0))
			return (free_buffer(&buffer));
		if (i == 0 && p > 0)
		{
			line = ft_substr(buffer, 0, p);
			p = 0;
			(void)free_buffer(&buffer);
			return (line);
		}
		if (ext_line(&buffer, &p, &line) == 1)
			return (line);
	}
}
