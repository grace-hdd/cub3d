#include "cub3d.h"

static int	is_walkable(char c)
{
	return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static int	neighbor_ok(t_game *game, int x, int y)
{
	if (x < 0 || y < 0 || x >= game->map.width || y >= game->map.height)
		return (0);
	return (game->map.grid[y][x] != ' ');
}

static int	cell_closed(t_game *game, int x, int y)
{
	return (neighbor_ok(game, x - 1, y) && neighbor_ok(game, x + 1, y)
		&& neighbor_ok(game, x, y - 1) && neighbor_ok(game, x, y + 1));
}

int	check_map_closed(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			if (is_walkable(game->map.grid[y][x]) && !cell_closed(game, x, y))
				return (print_error("the map is not closed by walls"));
			x++;
		}
		y++;
	}
	return (0);
}
