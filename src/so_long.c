/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cleticia <cleticia@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 21:24:37 by cleticia          #+#    #+#             */
/*   Updated: 2021/10/19 20:55:20 by cleticia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

static void	*open_img(t_map *map, char *filename)
{
	int		height;
	int		width;
	void	*ptr;

	height = 0;
	width = 0;
	ptr = mlx_xpm_file_to_image(map->mlx.mlx_ptr, filename, &width, &height);
	if (!height || !width)
	{
		write(2, "Error\n", 6);
		write(2, "Without image\n", 14);
		exit(1);
	}
	return (ptr);
}

static void	path_img(t_map *map)
{
	map->img.gamer1 = open_img(map, "./img/gamer1.xpm");
	map->img.exit = open_img(map, "./img/exit.xpm");
	map->img.wall = open_img(map, "./img/wall.xpm");
	map->img.collect = open_img(map, "./img/collect.xpm");
}

void	free_pointers(t_map *map)
{
	free(map->mlx.mlx_ptr);
	free_map(map);
}

int	end_program(t_map *map)
{
	if (map->img.gamer1 != 0)
		mlx_destroy_image(map->mlx.mlx_ptr, map->img.gamer1);
	if (map->img.exit != 0)
		mlx_destroy_image(map->mlx.mlx_ptr, map->img.exit);
	if (map->img.wall != 0)
		mlx_destroy_image(map->mlx.mlx_ptr, map->img.wall);
	if (map->img.collect != 0)
		mlx_destroy_image(map->mlx.mlx_ptr, map->img.collect);
	mlx_destroy_image (map->mlx.mlx_ptr, map->mlx.back.ptr_img);
	mlx_destroy_window(map->mlx.mlx_ptr, map->mlx.win);
	mlx_destroy_display(map->mlx.mlx_ptr);
	free_pointers(map);
	exit (0);
}

void	so_long(char *filename)
{
	t_map	map;
	int		x;
	int		y;

	parsing_map(&map, filename);
	map.mlx.mlx_ptr = mlx_init();
	x = map.width * 32;
	y = map.height * 32;
	map.mlx.win = mlx_new_window(map.mlx.mlx_ptr, x, y, "so_long");
	path_img(&map);
	paint_map(&map);
	mlx_hook(map.mlx.win, X_EVENT_KEY_PRESS, 1 << 0, event_key, &map);
	mlx_expose_hook(map.mlx.win, minimize_window, &map);
	mlx_hook(map.mlx.win, X_EVENT_KEY_EXIT, 1 << 0, end_program, &map);
	mlx_loop(map.mlx.mlx_ptr);
}
