/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grhaddad <grhaddad@student.42beirut.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 23:45:24 by grhaddad          #+#    #+#             */
/*   Updated: 2026/11/11 23:45:25 by grhaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	valid_char(char c)
{
	return (c == '0' || c == '1' || c == 'N'
		|| c == 'S' || c == 'E' || c == 'W' || c == ' ');
}

int	valid_line(char *line)
{
	int	i;

	if (is_blank(line))
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

int	map_end(t_game *game)
{
	int	end;

	end = game->nb_lines;
	while (end > game->map_start + 1 && is_blank(game->lines[end - 1]))
		end--;
	return (end);
}

int	map_width(t_game *game, int end)
{
	int	i;
	int	width;
	int	len;

	width = 0;
	i = game->map_start;
	while (i < end)
	{
		len = ft_strlen(game->lines[i]);
		if (len > width)
			width = len;
		i++;
	}
	return (width);
}

void	copy_row(t_game *game, int row, int width)
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
