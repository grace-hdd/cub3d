#include "cub3d.h"

static int	get_index(char *line)
{
	if (!ft_strncmp(line, "NO", 2))
		return (NO);
	if (!ft_strncmp(line, "SO", 2))
		return (SO);
	if (!ft_strncmp(line, "WE", 2))
		return (WE);
	if (!ft_strncmp(line, "EA", 2))
		return (EA);
	return (-1);
}

static int	check_path(char *path)
{
	size_t	len;
	int		fd;

	len = ft_strlen(path);
	if (len <= 4 || ft_strncmp(path + len - 4, ".xpm", 4) != 0)
		return (print_error("a texture file must have the .xpm extension"));
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (print_error("cannot open a texture file"));
	close(fd);
	return (0);
}

/* returns 0 = stored, 1 = error, -1 = not a texture line */
int	parse_texture(char *line, t_game *game)
{
	int		i;
	size_t	len;
	char	*start;

	i = get_index(line);
	if (i < 0 || (line[2] && !is_space(line[2])))
		return (-1);
	if (game->cfg.tex[i])
		return (print_error("duplicate texture identifier"));
	start = line + 2;
	while (is_space(*start))
		start++;
	len = ft_strlen(start);
	while (len > 0 && is_space(start[len - 1]))
		len--;
	if (len == 0)
		return (print_error("missing texture path"));
	game->cfg.tex[i] = ft_substr(start, 0, len);
	if (!game->cfg.tex[i])
		return (print_error("memory allocation failed"));
	if (ft_strchr(game->cfg.tex[i], ' ') || ft_strchr(game->cfg.tex[i], '\t'))
		return (print_error("a texture identifier takes only one path"));
	return (check_path(game->cfg.tex[i]));
}
