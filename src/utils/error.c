#include "cub3d.h"

int	print_error(char *msg)
{
	ft_putstr_fd("Error\n", 2);
	ft_putendl_fd(msg, 2);
	return (1);
}

void	init_game(t_game *game)
{
	ft_bzero(game, sizeof(t_game));
	game->cfg.floor = -1;
	game->cfg.ceiling = -1;
}

void	free_game(t_game *game)
{
	int	i;

	i = 0;
	while (i < NB_TEX)
	{
		free(game->cfg.tex[i]);
		game->cfg.tex[i] = NULL;
		i++;
	}
	i = 0;
	while (game->map.grid && i < game->map.height)
		free(game->map.grid[i++]);
	free(game->map.grid);
	game->map.grid = NULL;
}
