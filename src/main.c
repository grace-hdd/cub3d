#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_game	game;

	if (check_args(argc, argv))
		return (1);
	init_game(&game);
	if (read_file(argv[1], &game))
		return (free_game(&game), 1);
	if (parse_textures(&game))
		return (free_game(&game), 1);
	free_game(&game);
	return (0);
}
