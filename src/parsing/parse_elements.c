#include "cub3d.h"

static int	is_blank(char *line)
{
	int	i;

	i = 0;
	while (is_space(line[i]))
		i++;
	return (line[i] == '\0');
}

static int	all_elements(t_game *game)
{
	int	i;

	i = 0;
	while (i < NB_TEX)
		if (!game->cfg.tex[i++])
			return (0);
	return (game->cfg.floor != -1 && game->cfg.ceiling != -1);
}

static int	parse_element(char *line, t_game *game)
{
	int	ret;

	ret = parse_texture(line, game);
	if (ret == -1)
		ret = parse_color(line, game);
	return (ret);
}

static int	is_element_line(char *line)
{
	int	i;

	i = 0;
	while (i < NB_TEX)
	{
		if (!ft_strncmp(line, (char *[]){"NO", "SO", "WE", "EA"}[i], 2)
			&& (!line[2] || is_space(line[2])))
			return (1);
		i++;
	}
	return ((line[0] == 'F' || line[0] == 'C')
		&& (!line[1] || is_space(line[1])));
}

/* a line after the map start must not be an element */
static int	check_after_map(t_game *game, int i)
{
	while (i < game->nb_lines)
	{
		if (is_element_line(game->lines[i]))
			return (print_error("an element cannot come after the map"));
		i++;
	}
	return (0);
}

static int	is_map_line(char *line)
{
	return (line[0] == '1' || line[0] == '0' || is_space(line[0]));
}

int	parse_elements(t_game *game)
{
	int	i;
	int	ret;

	i = 0;
	while (i < game->nb_lines)
	{
		ret = parse_element(game->lines[i], game);
		if (ret == 1)
			return (1);
		if (ret == -1 && !is_blank(game->lines[i]))
		{
			if (!is_map_line(game->lines[i]))
				return (print_error("unknown identifier in the map file"));
			break ;
		}
		i++;
	}
	if (i == game->nb_lines)
		return (print_error("no map found in the file"));
	if (!all_elements(game))
		return (print_error("missing element before the map"));
	game->map_start = i;
	return (check_after_map(game, i + 1));
}
