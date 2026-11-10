#include "cub3d.h"

/* stops mlx_loop; main then frees everything with free_game */
int	close_game(t_game *game)
{
	mlx_loop_end(game->mlx);
	return (0);
}

int	key_press(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		close_game(game);
	return (0);
}

void	run_game(t_game *game)
{
	mlx_hook(game->win, 2, 1L << 0, key_press, game);
	mlx_hook(game->win, 17, 0, close_game, game);
	draw_background(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.ptr, 0, 0);
	mlx_loop(game->mlx);
}
