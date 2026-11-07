/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_element_checks.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grhaddad <grhaddad@student.42beirut.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 23:52:09 by grhaddad          #+#    #+#             */
/*   Updated: 2026/11/07 23:53:20 by grhaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static const char	*texture_id(int i)
{
	if (i == NO)
		return ("NO");
	if (i == SO)
		return ("SO");
	if (i == WE)
		return ("WE");
	return ("EA");
}

int	is_element_line(char *line)
{
	int	i;

	i = 0;
	while (i < NB_TEX)
	{
		if (!ft_strncmp(line, texture_id(i), 2)
			&& (!line[2] || is_space(line[2])))
			return (1);
		i++;
	}
	return ((line[0] == 'F' || line[0] == 'C')
		&& (!line[1] || is_space(line[1])));
}
