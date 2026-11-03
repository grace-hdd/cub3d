#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_game	game;

	if (check_args(argc, argv))
		return (1);
	init_game(&game);
	free_game(&game);
	return (0);
}
