/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grhaddad <grhaddad@student.42beirut.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 23:47:08 by grhaddad          #+#    #+#             */
/*   Updated: 2026/11/07 23:47:09 by grhaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

	destroy_window(game);
	i = 0;
	while (i < NB_TEX)
	{
		free(game->cfg.tex[i]);
		game->cfg.tex[i] = NULL;
		i++;
	}
	i = 0;
	while (game->lines && i < game->nb_lines)
		free(game->lines[i++]);
	free(game->lines);
	game->lines = NULL;
	game->nb_lines = 0;
	i = 0;
	while (game->map.grid && i < game->map.height)
		free(game->map.grid[i++]);
	free(game->map.grid);
	game->map.grid = NULL;
}
