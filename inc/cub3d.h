/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grhaddad <grhaddad@student.42beirut.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 23:50:50 by grhaddad          #+#    #+#             */
/*   Updated: 2026/11/07 23:53:11 by grhaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include "libft.h"
# include <fcntl.h>
# include <stdio.h>
# include "mlx.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# define WIN_W 1280
# define WIN_H 720
# define NB_TEX 4
# define NO 0
# define SO 1
# define WE 2
# define EA 3

typedef struct s_config
{
	char	*tex[NB_TEX];
	int		floor;
	int		ceiling;
}			t_config;

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
}			t_map;

typedef struct s_player
{
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	char	spawn;
}			t_player;

typedef struct s_img
{
	void	*ptr;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}			t_img;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_img		img;
	t_config	cfg;
	t_map		map;
	t_player	player;
	char		**lines;
	int			nb_lines;
	int			map_start;
}				t_game;

/* utils */
int		print_error(char *msg);
void	free_game(t_game *game);
void	init_game(t_game *game);

/* parsing */
int		check_args(int argc, char **argv);
int		read_file(char *path, t_game *game);
int		parse_texture(char *line, t_game *game);
int		parse_elements(t_game *game);
int		parse_color(char *line, t_game *game);
int		parse_map(t_game *game);
int		parse_player(t_game *game);
int		check_map_closed(t_game *game);
int		is_space(char c);
int		is_blank(char *line);
int		is_element_line(char *line);

/* render */
void	init_player_view(t_game *game);
int		init_window(t_game *game);
void	put_pixel(t_img *img, int x, int y, int color);
void	destroy_window(t_game *game);

/* get_next_line */
char	*get_next_line(int fd);
char	*ft_strjoin_gnl(char *s1, char const *s2);

#endif
