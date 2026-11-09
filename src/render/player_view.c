/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_view.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grhaddad <grhaddad@student.42beirut.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/08 00:00:00 by grhaddad          #+#    #+#             */
/*   Updated: 2026/11/08 00:00:00 by grhaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_direction(t_player *player)
{
	player->dir_x = 0;
	player->dir_y = 0;
	if (player->spawn == 'N')
		player->dir_y = -1;
	else if (player->spawn == 'S')
		player->dir_y = 1;
	else if (player->spawn == 'E')
		player->dir_x = 1;
	else if (player->spawn == 'W')
		player->dir_x = -1;
}

static void	set_camera_plane(t_player *player)
{
	player->plane_x = -player->dir_y * 0.66;
	player->plane_y = player->dir_x * 0.66;
}

void	init_player_view(t_game *game)
{
	game->player.x += 0.5;
	game->player.y += 0.5;
	set_direction(&game->player);
	set_camera_plane(&game->player);
}
