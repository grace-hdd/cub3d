/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grhaddad <grhaddad@student.42beirut.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 23:46:58 by grhaddad          #+#    #+#             */
/*   Updated: 2026/11/07 23:52:22 by grhaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\r'
		|| c == '\v' || c == '\f');
}

int	is_blank(char *line)
{
	int	i;

	i = 0;
	while (is_space(line[i]))
		i++;
	return (line[i] == '\0');
}
