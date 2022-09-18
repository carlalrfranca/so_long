/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cleticia <cleticia@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 16:20:39 by cleticia          #+#    #+#             */
/*   Updated: 2021/10/14 16:20:32 by cleticia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdio.h>
# include <stdlib.h>
# include <stddef.h>
# include <unistd.h>
# include <fcntl.h>
# include "../mlx/mlx.h"
# include "./get_next_line.h"
# include "../libft/libft.h"

typedef struct s_background
{
	void	*ptr_img;
	int	*data;
	int	line_size;
	int	bpp;
	int	endian;
}	t_background;

typedef struct s_mlx
{
	t_background	back;
	void		*mlx_ptr;
	void		*win;
}	t_mlx;

typedef struct s_image
{
	void	*collect;
	void	*exit;
	void	*gamer1;
	void	*wall;
}	t_image;

typedef struct s_map
{
	struct s_image	img;
	struct s_mlx	mlx;
	char	**map;
	int	collect;
	int	counter;
	int	empty;
	int	height;
	int	width;
	int	x;
	int	y;
	int	fd;
}	t_map;

enum e_keycode
{
	KEY_A		= 97,
	KEY_D		= 100,
	KEY_S		= 115,
	KEY_W		= 119,
	KEY_ESC		= 65307,
	X_EVENT_KEY_EXIT	= 17,
	X_EVENT_KEY_PRESS	= 2
};

typedef struct s_check
{
	int	collect;
	int	exit;
	int	gamer;
}	t_check;

int	paint_map(t_map *map);
int	event_key(int keycode, t_map *map);
int	minimize_window(t_map *map);
int	end_program(t_map *map);
void	parsing_map(t_map *map, char *filename);
void	so_long(char *filename);
void	verif_map(t_map *map);
void	free_map(t_map *map);

#endif
