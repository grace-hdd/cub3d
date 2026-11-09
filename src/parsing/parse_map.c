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

static int	check_map_lines(t_game *game, int end)
{
	int	i;

	i = game->map_start;
	while (i < end)
	{
		if (!valid_line(game->lines[i]))
			return (print_error("invalid character or empty line in map"));
		i++;
	}
	return (0);
}

static int	build_grid(t_game *game)
{
	int	i;

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

int	parse_map(t_game *game)
{
	int	end;

	end = map_end(game);
	if (check_map_lines(game, end))
		return (1);
	game->map.height = end - game->map_start;
	game->map.width = map_width(game, end);
	return (build_grid(game));
}
