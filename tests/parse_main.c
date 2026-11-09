#include "cub3d.h"

/* same steps as src/main.c, without the window: the parser tests need no display */
int	main(int argc, char **argv)
{
	t_game	game;

	if (check_args(argc, argv))
		return (1);
	init_game(&game);
	if (read_file(argv[1], &game) || parse_elements(&game)
		|| parse_map(&game) || parse_player(&game)
		|| check_map_closed(&game))
		return (free_game(&game), 1);
	init_player_view(&game);
	free_game(&game);
	return (0);
}
