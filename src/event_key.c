/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_key.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cleticia <cleticia@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 21:24:37 by cleticia          #+#    #+#             */
/*   Updated: 2021/10/14 16:21:09 by cleticia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

int	minimize_window(t_map *map)
{
	mlx_destroy_image(map->mlx.mlx_ptr, map->mlx.back.ptr_img);
	paint_map(map);
	return (0);
}

static void	print_index(t_map *map)
{
	char	*str;

	map->counter++;
	str = ft_itoa (map->counter);
	write (1, str, ft_strlen(str));
	write (1, "\n", 1);
	free (str);
}

static void	move_gammer(t_map *map, int x, int y)
{
	if (x < map->height && y < map->width && x >= 0 && y >= 0)
	{
		if (map->map[x][y] == 'E')
		{
			if (map->collect == 0)
			{
				write (1, "Congratulations!!!You got all coins.\n", 37);
				end_program(map);
			}
		}
		else if (map->map[x][y] != '1')
		{
			if (map->map[x][y] == 'C')
				map->collect--;
			map->map[map->x][map->y] = '0';
			map->x = x;
			map->y = y;
			map->map[x][y] = 'P';
			print_index (map);
			mlx_destroy_image(map->mlx.mlx_ptr, map->mlx.back.ptr_img);
			paint_map(map);
		}
	}
}

int	event_key(int keycode, t_map *map)
{
	if (keycode == KEY_ESC)
	{
		write (1, "You typed the ESC key. Game closed!\n", 36);
		end_program(map);
	}
	if (keycode == KEY_A)
		move_gammer(map, map->x, map->y - 1);
	if (keycode == KEY_D)
		move_gammer(map, map->x, map->y + 1);
	if (keycode == KEY_S)
		move_gammer(map, map->x + 1, map->y);
	if (keycode == KEY_W)
		move_gammer(map, map->x - 1, map->y);
	return (0);
}
