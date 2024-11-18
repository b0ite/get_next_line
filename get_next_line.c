/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilbert <igilbert@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 10:18:06 by igilbert          #+#    #+#             */
/*   Updated: 2024/11/18 11:27:08 by igilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	read_test(int fd, char *buffer, char **line, int position)
{
	int	bytes_read;

	bytes_read = 1;
	if (position == 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
		{
			free(*line);
			return (0);
		}
		buffer[bytes_read] = '\0';
	}
	return (1);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	int			position;
	char		*line;
	int			i;

	line = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!line)
		return (NULL);
	i = 0;
	position = 0;
	while (1)
	{
		if (!read_test(fd, buffer, &line, position))
			return (NULL);
		while (buffer[position] && buffer[position] != '\n')
			line[i++] = buffer[position++];
		if (buffer[position] == '\n')
		{
			line[i++] = buffer[position++];
			line[i] = '\0';
			return (line);
		}
		position = 0;
	}
}
