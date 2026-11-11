/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grhaddad <grhaddad@student.42beirut.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 23:44:41 by grhaddad          #+#    #+#             */
/*   Updated: 2026/11/11 23:44:42 by grhaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* stops mlx_loop; main then frees everything with free_game */
int	close_game(t_game *game)
{
	mlx_loop_end(game->mlx);
	return (0);
}

static int	render_frame(t_game *game)
{
	draw_background(game);
	draw_walls(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.ptr, 0, 0);
	return (0);
}

void	run_game(t_game *game)
{
	mlx_hook(game->win, 2, 1L << 0, key_press, game);
	mlx_hook(game->win, 3, 1L << 1, key_release, game);
	mlx_hook(game->win, 17, 0, close_game, game);
	mlx_loop_hook(game->mlx, render_frame, game);
	render_frame(game);
	mlx_loop(game->mlx);
}
