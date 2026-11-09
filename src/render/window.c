#include "cub3d.h"

int	init_window(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (print_error("cannot connect to the display"));
	game->win = mlx_new_window(game->mlx, WIN_W, WIN_H, "cub3D");
	if (!game->win)
		return (print_error("cannot create the window"));
	game->img.ptr = mlx_new_image(game->mlx, WIN_W, WIN_H);
	if (!game->img.ptr)
		return (print_error("cannot create the image"));
	game->img.addr = mlx_get_data_addr(game->img.ptr, &game->img.bpp,
			&game->img.line_len, &game->img.endian);
	if (!game->img.addr)
		return (print_error("cannot read the image buffer"));
	return (0);
}

void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= WIN_W || y >= WIN_H)
		return ;
	dst = img->addr + y * img->line_len + x * (img->bpp / 8);
	*(unsigned int *)dst = color;
}

void	destroy_window(t_game *game)
{
	if (game->img.ptr)
		mlx_destroy_image(game->mlx, game->img.ptr);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	game->img.ptr = NULL;
	game->win = NULL;
	game->mlx = NULL;
}
