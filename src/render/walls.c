#include "cub3d.h"

static void	draw_wall_line(t_game *game, int x, t_ray *ray)
{
	int	line_height;
	int	start;
	int	end;
	int	y;

	line_height = (int)(WIN_H / ray->perp_dist);
	start = WIN_H / 2 - line_height / 2;
	end = WIN_H / 2 + line_height / 2;
	if (start < 0)
		start = 0;
	if (end >= WIN_H)
		end = WIN_H - 1;
	y = start;
	while (y <= end)
	{
		put_pixel(&game->img, x, y, 0x808080);
		y++;
	}
}

void	draw_walls(t_game *game)
{
	t_ray	ray;
	int		x;

	x = 0;
	while (x < WIN_W)
	{
		cast_ray(game, x, &ray);
		draw_wall_line(game, x, &ray);
		x++;
	}
}
