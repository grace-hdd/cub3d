/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grhaddad <grhaddad@student.42beirut.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 23:47:30 by grhaddad          #+#    #+#             */
/*   Updated: 2026/11/07 23:47:31 by grhaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_game	game;

	if (check_args(argc, argv))
		return (1);
	init_game(&game);
	if (read_file(argv[1], &game))
		return (free_game(&game), 1);
	if (parse_elements(&game))
		return (free_game(&game), 1);
	if (parse_map(&game))
		return (free_game(&game), 1);
	free_game(&game);
	return (0);
}
