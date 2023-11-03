/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthor <jthor@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 20:05:30 by jthor             #+#    #+#             */
/*   Updated: 2023/09/13 20:05:32 by jthor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static char	*reset_buffer(char *buffer)
{
	char	*reset;
	int		i;
	int		j;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free (buffer);
		return (0);
	}
	reset = ft_calloc((ft_strlen(buffer) - i + 1), sizeof(char));
	i++;
	j = 0;
	while (buffer[i])
		reset[j++] = buffer[i++];
	free(buffer);
	buffer = 0;
	return (reset);
}

static char	*print_line(char *buffer)
{
	char	*line;
	int		i;

	i = 0;
	if (!buffer[i])
		return (0);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	line = ft_calloc((i + 2), sizeof(char));
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] && buffer[i] == '\n')
		line[i] = '\n';
	return (line);
}

static char	*join_and_free(char *buffer, char *temp)
{
	char	*pepega;

	pepega = ft_strjoin(buffer, temp);
	free(buffer);
	buffer = 0;
	return (pepega);
}

static char	*read_file(char *buffer, int fd)
{
	char	*temp;
	int		byte_read;

	temp = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	byte_read = 1;
	while (!ft_strchr(temp, '\n') && byte_read > 0)
	{
		byte_read = read(fd, temp, BUFFER_SIZE);
		if (byte_read == -1)
		{
			free(temp);
			return (0);
		}
		temp[byte_read] = 0;
		buffer = join_and_free(buffer, temp);
	}
	free(temp);
	temp = 0;
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (0);
	if (buffer == NULL)
		buffer = ft_calloc(1, sizeof(char));
	buffer = read_file(buffer, fd);
	if (!buffer)
		return (0);
	line = print_line(buffer);
	buffer = reset_buffer(buffer);
	return (line);
}
