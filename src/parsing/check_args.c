/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grhaddad <grhaddad@student.42beirut.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 23:46:37 by grhaddad          #+#    #+#             */
/*   Updated: 2026/11/07 23:46:38 by grhaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	has_cub_extension(char *path)
{
	size_t	len;

	len = ft_strlen(path);
	if (len <= 4)
		return (0);
	return (ft_strncmp(path + len - 4, ".cub", 4) == 0);
}

static int	can_read_file(char *path)
{
	int		fd;
	char	c;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	if (read(fd, &c, 1) < 0)
	{
		close(fd);
		return (0);
	}
	close(fd);
	return (1);
}

int	check_args(int argc, char **argv)
{
	if (argc != 2)
		return (print_error("usage: ./cub3D <map.cub>"));
	if (!has_cub_extension(argv[1]))
		return (print_error("the map file must have the .cub extension"));
	if (!can_read_file(argv[1]))
		return (print_error("cannot open the map file"));
	return (0);
}
