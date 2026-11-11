/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grhaddad <grhaddad@student.42beirut.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 23:44:34 by grhaddad          #+#    #+#             */
/*   Updated: 2026/11/11 23:44:35 by grhaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* ceiling color on the top half of the image, floor color on the bottom half */
void	draw_background(t_game *game)
{
	int	x;
	int	y;
	int	color;

	y = 0;
	while (y < WIN_H)
	{
		color = game->cfg.ceiling;
		if (y >= WIN_H / 2)
			color = game->cfg.floor;
		x = 0;
		while (x < WIN_W)
		{
			put_pixel(&game->img, x, y, color);
			x++;
		}
		y++;
	}
}
