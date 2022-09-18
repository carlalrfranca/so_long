/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cleticia <cleticia@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 21:24:37 by cleticia          #+#    #+#             */
/*   Updated: 2021/10/19 20:56:41 by cleticia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

void	free_map(t_map *map)
{
	int	x;

	x = -1;
	while (++x < map->height)
		free(map->map[x]);
	free(map->map);
}

static void	map_error(t_map *map)
{
	free_map(map);
	write(2, "Error\n", 6);
	write(2, "Invalid Map\n", 12);
	exit(1);
}

static void	verif_char(t_map *map, t_check *check, char letter)
{
	if (letter != '0' && letter != '1' && letter != 'C'
		&& letter != 'E' && letter != 'P')
		map_error(map);
	if (letter == 'C')
		check->collect++;
	if (letter == 'E')
		check->exit = 1;
	if (letter == 'P')
	{
		if (check->gamer == 1)
			map_error(map);
		else
			check->gamer = 1;
	}
}

static void	gamer_position(t_map *map, int x, int y, char letter)
{
	if (letter == '0')
		map->empty = map->empty + 1;
	if (letter == 'P')
	{
		map->x = x;
		map->y = y;
	}
}

void	verif_map(t_map *map)
{
	t_check	check;
	int		x;
	int		y;

	x = -1;
	check = (t_check){0, 0, 0};
	map->empty = 0;
	while (++x < map->height)
	{
		y = -1;
		while (++y < map->width)
		{
			if (x == 0 || y == 0 || x == map->height - 1 || y == map->width - 1)
				if (map->map[x][y] != '1')
					map_error(map);
			if (map->map[x][y] != '0')
				verif_char(map, &check, map->map[x][y]);
			gamer_position(map, x, y, map->map[x][y]);
		}
	}
	map->collect = check.collect;
	if (!check.collect || !check.exit || !check.gamer)
		map_error(map);
}
