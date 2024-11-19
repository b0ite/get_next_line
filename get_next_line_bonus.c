/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilbert <igilbert@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 10:18:06 by igilbert          #+#    #+#             */
/*   Updated: 2024/11/19 13:10:37 by igilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	full_read(t_buff both, int fd)
{
	char	*tmp;
	int		i;

	tmp = ft_realloc(both->buffer, both->p, both->p + BUFFER_SIZE);
	if (!tmp)
	{
		free(*both->buffer);
		*both->buffer = NULL;
		*both->p = 0;
		return (-1);
	}
	*both->buffer = tmp;
	i = read(fd, *both->buffer + *both->p, BUFFER_SIZE);
	if (i < 0)
	{
		free(*both->buffer);
		*both->buffer = NULL;
		*both->p = 0;
		return (-1);
	}
	if (i > 0)
		*both->p += i;
	(*both->buffer)[*both->p] = '\0';
	return (i);
}

int	get_line(t_buff both)
{
	int	i;

	i = 0;
	while (i < both->p)
	{
		if (both->buffer[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

int	ext_line(t_buff both, char **line)
{
	char	*line_tmp;
	char	*tmp;
	int		i;

	i = get_line(*both->buffer, *both->p);
	if (i == -1)
		return (0);
	line_tmp = ft_substr(*both->buffer, 0, i + 1);
	tmp = ft_substr(*both->buffer, i + 1, *both->p - i - 1);
	if (*both->buffer)
		free(*both->buffer);
	*both->buffer = tmp;
	*both->p = *both->p - i - 1;
	*line = line_tmp;
	return (1);
}

char	*free_buffer(t_buff both)
{
	if (*both->buffer)
	{
		free(*both->buffer);
		*both->buffer = NULL;
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	static t_buff	*both;
	char			*line;
	int				i;

	if (fd < 0)
		return (free_buffer(&both->buffer));
	if (ext_line(&both->buffer, &both->p, &line) == 1)
		return (line);
	while (1)
	{
		i = full_read(&both->buffer, &both->p, fd);
		if (i == -1 || (i == 0 && both->p == 0))
			return (free_buffer(&both->buffer));
		if (i == 0 && both->p > 0)
		{
			line = ft_substr(both->buffer, 0, both->p);
			both->p = 0;
			(void)free_buffer(&both->buffer);
			return (line);
		}
		if (ext_line(&both->buffer, &both->p, &line) == 1)
			return (line);
	}
}
