/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grhaddad <grhaddad@student.42beirut.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/06 23:18:45 by grhaddad          #+#    #+#             */
/*   Updated: 2026/11/06 23:18:50 by grhaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	parse_value(char **str, int *value)
{
	int	start;

	while (is_space(**str))
		(*str)++;
	start = 0;
	while ((*str)[start] >= '0' && (*str)[start] <= '9')
		start++;
	if (start == 0 || start > 3)
		return (1);
	*value = ft_atoi(*str);
	if (*value < 0 || *value > 255)
		return (1);
	*str += start;
	while (is_space(**str))
		(*str)++;
	return (0);
}

static int	parse_comma(char **str)
{
	if (**str != ',')
		return (1);
	(*str)++;
	return (0);
}

static int	parse_rgb(char *str, int *color)
{
	int	r;
	int	g;
	int	b;

	if (parse_value(&str, &r) || parse_comma(&str)
		|| parse_value(&str, &g) || parse_comma(&str)
		|| parse_value(&str, &b))
		return (1);
	while (is_space(*str))
		str++;
	if (*str != '\0')
		return (1);
	*color = (r << 16) | (g << 8) | b;
	return (0);
}

int	parse_color(char *line, t_game *game)
{
	int	*color;

	if ((line[0] != 'F' && line[0] != 'C')
		|| (line[1] && !is_space(line[1])))
		return (-1);
	if (line[0] == 'F')
		color = &game->cfg.floor;
	else
		color = &game->cfg.ceiling;
	if (*color != -1)
		return (print_error("duplicate color identifier"));
	while (is_space(line[1]))
		line++;
	if (parse_rgb(line + 1, color))
		return (print_error("invalid color"));
	return (0);
}
