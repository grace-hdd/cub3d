/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grhaddad <grhaddad@student.42beirut.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 23:07:18 by grhaddad          #+#    #+#             */
/*   Updated: 2026/11/07 23:43:20 by grhaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	valid_char(char c)
{
	return (c == '0' || c == '1' || c == 'N'
		|| c == 'S' || c == 'E' || c == 'W' || c == ' ');
}

static int	valid_line(char *line)
{
	int	i;

	if (line[0] == '\0')
		return (0);
	i = 0;
	while (line[i])
	{
		if (!valid_char(line[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	map_width(t_game *game)
{
	int	i;
	int	width;
	int	len;

	width = 0;
	i = game->map_start;
	while (i < game->nb_lines)
	{
		len = ft_strlen(game->lines[i]);
		if (len > width)
			width = len;
		i++;
	}
	return (width);
}

static void	copy_row(t_game *game, int row, int width)
{
	int	i;

	i = 0;
	while (i < width)
	{
		if (game->lines[game->map_start + row][i])
			game->map.grid[row][i] = game->lines[game->map_start + row][i];
		else
			game->map.grid[row][i] = ' ';
		i++;
	}
	game->map.grid[row][i] = '\0';
}

int	parse_map(t_game *game)
{
	int	i;
	int	width;

	i = game->map_start;
	while (i < game->nb_lines)
	{
		if (!valid_line(game->lines[i]))
			return (print_error("invalid character or empty line in map"));
		i++;
	}
	game->map.height = game->nb_lines - game->map_start;
	game->map.width = map_width(game);
	game->map.grid = ft_calloc(game->map.height, sizeof(char *));
	if (!game->map.grid)
		return (print_error("memory allocation failed"));
	i = 0;
	while (i < game->map.height)
	{
		game->map.grid[i] = ft_calloc(game->map.width + 1, sizeof(char));
		if (!game->map.grid[i])
			return (print_error("memory allocation failed"));
		copy_row(game, i, game->map.width);
		i++;
	}
	return (0);
}
