/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grhaddad <grhaddad@student.42beirut.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 23:47:26 by grhaddad          #+#    #+#             */
/*   Updated: 2026/11/07 23:47:27 by grhaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*readfd(int fd, char *line)
{
	char		*save;
	ssize_t		countread;

	save = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!save)
		return (free(line), NULL);
	countread = 1;
	while (countread > 0 && !ft_strchr(line, '\n'))
	{
		countread = read(fd, save, BUFFER_SIZE);
		if (countread > 0)
		{
			save[countread] = '\0';
			line = ft_strjoin_gnl(line, save);
			if (!line)
				return (free(save), free(line), NULL);
		}
	}
	if (countread == 0 && (!line || !*line))
		return (free(save), free(line), NULL);
	if (countread < 0)
		return (free(line), free(save), NULL);
	return (free(save), line);
}

static char	*init(int fd, char **line)
{
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!*line)
		*line = ft_strdup("");
	if (!*line)
		return (NULL);
	*line = readfd(fd, *line);
	if (!*line)
		return (NULL);
	return (*line);
}

static char	*split_current(char **line)
{
	char	*current;
	char	*nextline;

	if (ft_strchr(*line, '\n'))
	{
		current = ft_substr(*line, 0, ft_strchr(*line, '\n') - *line + 1);
		nextline = ft_strdup(ft_strchr(*line, '\n') + 1);
		if (!nextline || !current)
			return (free(*line), free(current), NULL);
		free(*line);
		*line = nextline;
	}
	else
	{
		current = ft_strdup(*line);
		if (!current)
			return (free(*line), NULL);
		free(*line);
		*line = NULL;
	}
	return (current);
}

char	*get_next_line(int fd)
{
	static char	*line;

	if (fd == -1)
		return (free(line), line = NULL, NULL);
	line = init(fd, &line);
	if (!line)
		return (NULL);
	return (split_current(&line));
}
