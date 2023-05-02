/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gloms <rbrendle@student.42mulhouse.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 19:01:26 by gloms             #+#    #+#             */
/*   Updated: 2023/05/02 16:49:52 by gloms            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int storage_analyser(char *storage)
{
	int i;

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

char *read_store(int fd, char *storage)
{
	int			retread;
	char 		*buf;

	retread = 1;
	while (retread > 0)
	{
		buf = malloc(sizeof(char) * BUFFER_SIZE + 1);
		if (!buf)
			return (free(storage), NULL);
		retread = read(fd, buf, BUFFER_SIZE);
		if (retread < 0)
			return(free(storage), NULL);
		buf[retread] = '\0';
		storage = ft_strjoin(storage, buf);
		if (storage == NULL)
			return (free(storage), NULL);
		free(buf);
		if (storage_analyser(storage) == 1)
			break;
	}
	return (storage);
}

char *define_returned_line(char **storage)
{
	int			len_storage;
	int			len_line;
	char		*returned_line;
	char		*temp_storage;

	temp_storage = ft_strdup(*storage);
	len_storage = ft_strlen(*storage);
	len_line = ft_strlen_gnl(*storage, '\n');
	returned_line = ft_substr(*storage, 0, len_line);
	free(*storage);
	*storage = ft_substr(temp_storage, len_line, (len_storage - len_line));
	free(temp_storage);
	return (returned_line);
}

char	*get_next_line(int fd)
{
	static char	*storage = NULL;
	char		*returned_line;
	if (!fd)
		return (NULL);
	storage = read_store(fd, storage);
	if (!storage)
		return (NULL);
	returned_line =	define_returned_line(&storage);
	if (returned_line && *returned_line == '\0')
	{
		free(returned_line);
		return (NULL);
	}
	return (returned_line);
}

