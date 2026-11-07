/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grhaddad <grhaddad@student.42beirut.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 23:47:04 by grhaddad          #+#    #+#             */
/*   Updated: 2026/11/07 23:47:05 by grhaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	count_lines(char *path)
{
	int		fd;
	int		count;
	char	*line;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (-1);
	count = 0;
	line = get_next_line(fd);
	while (line)
	{
		count++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (count);
}

static void	strip_newline(char *line)
{
	size_t	len;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
}

static int	fill_lines(char *path, t_game *game)
{
	int		fd;
	int		i;
	char	*line;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (1);
	i = 0;
	line = get_next_line(fd);
	while (line && i < game->nb_lines)
	{
		strip_newline(line);
		game->lines[i++] = line;
		line = get_next_line(fd);
	}
	free(line);
	get_next_line(-1);
	close(fd);
	return (i != game->nb_lines);
}

int	read_file(char *path, t_game *game)
{
	game->nb_lines = count_lines(path);
	if (game->nb_lines < 0)
		return (game->nb_lines = 0, print_error("cannot read the map file"));
	if (game->nb_lines == 0)
		return (print_error("the map file is empty"));
	game->lines = ft_calloc(game->nb_lines + 1, sizeof(char *));
	if (!game->lines)
		return (game->nb_lines = 0, print_error("memory allocation failed"));
	if (fill_lines(path, game))
		return (print_error("cannot read the map file"));
	return (0);
}
