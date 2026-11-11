/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grhaddad <grhaddad@student.42beirut.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 23:50:04 by grhaddad          #+#    #+#             */
/*   Updated: 2026/11/11 23:50:05 by grhaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_key_state(t_input *input, int keycode, int state)
{
	if (keycode == KEY_W)
		input->w = state;
	else if (keycode == KEY_A)
		input->a = state;
	else if (keycode == KEY_S)
		input->s = state;
	else if (keycode == KEY_D)
		input->d = state;
	else if (keycode == KEY_LEFT)
		input->left = state;
	else if (keycode == KEY_RIGHT)
		input->right = state;
}

int	key_press(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		close_game(game);
	set_key_state(&game->input, keycode, 1);
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	set_key_state(&game->input, keycode, 0);
	return (0);
}
