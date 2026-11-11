/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grhaddad <grhaddad@student.42beirut.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 23:44:53 by grhaddad          #+#    #+#             */
/*   Updated: 2026/11/11 23:44:54 by grhaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* walls, spaces and anything outside the grid stop the ray */
static int	is_wall(t_game *game, int x, int y)
{
	char	c;

	if (x < 0 || y < 0 || x >= game->map.width || y >= game->map.height)
		return (1);
	c = game->map.grid[y][x];
	return (c == '1' || c == ' ');
}

/* side_x: ray length to the first vertical grid line */
static void	init_step_x(t_game *game, t_ray *ray)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_x = (game->player.x - ray->map_x) * ray->delta_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_x = (ray->map_x + 1.0 - game->player.x) * ray->delta_x;
	}
}

static void	init_step_y(t_game *game, t_ray *ray)
{
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_y = (game->player.y - ray->map_y) * ray->delta_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_y = (ray->map_y + 1.0 - game->player.y) * ray->delta_y;
	}
}

static void	init_ray(t_game *game, int x, t_ray *ray)
{
	double	camera_x;

	camera_x = 2.0 * x / WIN_W - 1.0;
	ray->dir_x = game->player.dir_x + game->player.plane_x * camera_x;
	ray->dir_y = game->player.dir_y + game->player.plane_y * camera_x;
	ray->map_x = (int)game->player.x;
	ray->map_y = (int)game->player.y;
	ray->delta_x = 1e30;
	ray->delta_y = 1e30;
	if (ray->dir_x != 0)
		ray->delta_x = fabs(1.0 / ray->dir_x);
	if (ray->dir_y != 0)
		ray->delta_y = fabs(1.0 / ray->dir_y);
	init_step_x(game, ray);
	init_step_y(game, ray);
}

/* DDA for screen column x: fills hit cell, side and perp_dist */
void	cast_ray(t_game *game, int x, t_ray *ray)
{
	init_ray(game, x, ray);
	while (1)
	{
		if (ray->side_x < ray->side_y)
		{
			ray->side_x += ray->delta_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_y += ray->delta_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (is_wall(game, ray->map_x, ray->map_y))
			break ;
	}
	if (ray->side == 0)
		ray->perp_dist = ray->side_x - ray->delta_x;
	else
		ray->perp_dist = ray->side_y - ray->delta_y;
}
