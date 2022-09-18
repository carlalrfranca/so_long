/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paint_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cleticia <cleticia@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 21:24:37 by cleticia          #+#    #+#             */
/*   Updated: 2021/10/19 20:57:33 by cleticia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

void	color_background(t_map *map, int width, int height)
{
	int	x;
	int	y;

	map->mlx.back.ptr_img = mlx_new_image(map->mlx.mlx_ptr, width, height);
	map->mlx.back.data = (int *)mlx_get_data_addr(map->mlx.back.ptr_img,
			&map->mlx.back.bpp,
			&map->mlx.back.line_size, &map->mlx.back.endian);
	x = -1;
	while (++x < height)
	{
		y = -1;
		while (++y < width)
			map->mlx.back.data[x * width + y] = 0x000000;
	}
	mlx_put_image_to_window(map->mlx.mlx_ptr, map->mlx.win,
		map->mlx.back.ptr_img, 0, 0);
}

static void	put_image(t_map *map, int y, int x, char c)
{
	if (c == '1')
		mlx_put_image_to_window(map->mlx.mlx_ptr, map->mlx.win,
			map->img.wall, y, x);
	if (c == 'C')
		mlx_put_image_to_window(map->mlx.mlx_ptr, map->mlx.win,
			map->img.collect, y, x);
	if (c == 'E')
		mlx_put_image_to_window(map->mlx.mlx_ptr, map->mlx.win,
			map->img.exit, y, x);
	if (c == 'P')
		mlx_put_image_to_window(map->mlx.mlx_ptr, map->mlx.win,
			map->img.gamer1, y, x);
}

int	paint_map(t_map *map)
{
	int		x;
	int		y;

	color_background(map, map->width * 32, map->height * 32);
	x = -1;
	while (++x < map->height)
	{
		y = -1;
		while (++y < map->width)
		{
			if (map->map[x][y] == '1')
				put_image(map, y * 32, x * 32, '1');
			if (map->map[x][y] == 'C')
				put_image(map, y * 32, x * 32, 'C');
			if (map->map[x][y] == 'E')
				put_image(map, y * 32, x * 32, 'E');
			if (map->map[x][y] == 'P')
				put_image(map, y * 32, x * 32, 'P');
		}
	}
	return (0);
}
