/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtavabil <rtavabil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 13:13:34 by rtavabil          #+#    #+#             */
/*   Updated: 2024/02/12 17:06:24 by rtavabil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*trim_buffer(char *buffer)
{
	char	*trimmed_buffer;
	int		new_line;

	new_line = ft_strchr(buffer, '\n');
	if (new_line == -1)
	{
		free(buffer);
		return (NULL);
	}
	trimmed_buffer = ft_substr(buffer, new_line + 1, \
			ft_strlen(buffer) - new_line);
	if (!trimmed_buffer)
	{
		free(trimmed_buffer);
		return (NULL);
	}
	free(buffer);
	return (trimmed_buffer);
}

char	*get_buffer(int fd, char *buffer)
{
	int		bytes;
	int		new_line;
	char	*read_b;

	read_b = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!read_b)
		return (NULL);
	bytes = 1;
	new_line = ft_strchr(buffer, '\n');
	while (new_line == -1 && bytes != 0)
	{
		bytes = read(fd, read_b, BUFFER_SIZE);
		if (bytes == -1)
		{
			free(read_b);
			free(buffer);
			return (NULL);
		}
		read_b[bytes] = '\0';
		buffer = ft_strjoin(buffer, read_b);
		new_line = ft_strchr(buffer, '\n');
	}
	free(read_b);
	return (buffer);
}

char	*return_line(char *buffer)
{
	int		new_line;
	char	*line;

	if (!*buffer)
		return (NULL);
	new_line = ft_strchr(buffer, '\n');
	if (new_line == -1)
	{
		line = (char *)malloc((ft_strlen(buffer) + 1) * sizeof(char));
		if (!line)
			return (NULL);
		line = ft_memcpy(line, buffer, ft_strlen(buffer) + 1);
		return (line);
	}
	line = ft_substr(buffer, 0, new_line + 1);
	if (!line)
		return (NULL);
	return (line);
}

int	get_next_line(int fd, char **line, char **buffer)
{
	if (fd < 0 || BUFFER_SIZE < 1)
		return (-1);
	*buffer = get_buffer(fd, *buffer);
	if (!*buffer)
		return (-1);
	*line = return_line(*buffer);
	*buffer = trim_buffer(*buffer);
	return (0);
}
