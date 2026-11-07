/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grhaddad <grhaddad@student.42beirut.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/08 00:11:00 by grhaddad          #+#    #+#             */
/*   Updated: 2026/11/08 00:11:00 by grhaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_spawn(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static void	set_player(t_game *game, int x, int y, char spawn)
{
	game->player.x = x;
	game->player.y = y;
	game->player.spawn = spawn;
}

static int	scan_players(t_game *game)
{
	int		x;
	int		y;
	int		count;

	count = 0;
	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			if (is_spawn(game->map.grid[y][x]))
			{
				count++;
				set_player(game, x, y, game->map.grid[y][x]);
			}
			x++;
		}
		y++;
	}
	return (count);
}

int	parse_player(t_game *game)
{
	int	count;

	count = scan_players(game);
	if (count == 0)
		return (print_error("no player in the map"));
	if (count > 1)
		return (print_error("multiple players in the map"));
	return (0);
}
