/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gloms <rbrendle@student.42mulhouse.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 19:01:26 by gloms             #+#    #+#             */
/*   Updated: 2023/05/05 15:47:12 by gloms            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	storage_analyser(char *storage)
{
	int	i;

	i = 0;
	if (!storage)
		return (0);
	while (storage[i])
	{
		if (storage[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*read_store(int fd, char *storage)
{
	int		retread;
	char	*buf;

	retread = 1;
	while (retread > 0)
	{
		buf = malloc(sizeof(char) * BUFFER_SIZE + 1);
		if (!buf)
			return (free(storage), NULL);
		retread = read(fd, buf, BUFFER_SIZE);
		if (retread < 0)
		{
			free(buf);
			storage = NULL;
			return (free(storage), NULL);
		}
		buf[retread] = '\0';
		storage = ft_strjoin(storage, buf);
		free(buf);
		if (storage == NULL)
			return (free(storage), NULL);
		if (storage_analyser(storage) == 1)
			break ;
	}
	return (storage);
}

char	*define_returned_line(char **storage)
{
	int		len_storage;
	int		len_line;
	char	*returned_line;
	char	*temp_storage;

	temp_storage = ft_strdup(*storage);
	len_storage = ft_strlen(*storage);
	len_line = ft_strlen_gnl(*storage, '\n');
	returned_line = ft_substr(*storage, 0, len_line);
	free(*storage);
	*storage = ft_substr(temp_storage, len_line, (len_storage - len_line));
	free(temp_storage);
	if (!*storage)
	{
		free(returned_line);
		return (NULL);
	}
	return (returned_line);
}

char	*get_next_line(int fd)
{
	static char	*storage[4096];
	char		*returned_line;

	if (BUFFER_SIZE < 1 || fd < 0 || read(fd, NULL, 0) < 0)
	{
		free(storage[fd]);
		storage[fd] = NULL;
		return (NULL);
	}
	storage[fd] = read_store(fd, storage[fd]);
	if (!storage[fd])
		return (NULL);
	returned_line = define_returned_line(&storage[fd]);
	if (!returned_line || (returned_line && *returned_line == '\0'))
	{
		free(returned_line);
		free(storage[fd]);
		return (storage[fd] = NULL);
	}
	if (storage[fd] && storage[fd][0] == 0)
	{
		free(storage[fd]);
		storage[fd] = NULL;
	}
	return (returned_line);
}
