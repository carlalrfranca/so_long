/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cleticia <cleticia@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 21:24:37 by cleticia          #+#    #+#             */
/*   Updated: 2021/10/19 20:57:27 by cleticia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

void	parsing_error(void)
{
	write(2, "Error\n", 6);
	write(2, "Invalid Map\n", 12);
	exit(1);
}

static int	file_sz(t_map *map, size_t *size, char **line, int *vld)
{
	int	ret;

	ret = get_next_line(map->fd, line);
	if (ret == 0 && *size == 0)
	{
		close(map->fd);
		free (*line);
		parsing_error();
	}
	if (!*size)
		*size = ft_strlen (*line);
	else if (*size != ft_strlen (*line))
		*vld = 1;
	free (*line);
	map->height += 1;
	return (ret);
}

int	render_map(char *filename, t_map *map)
{
	char	*line;
	size_t	size;
	int		ret;
	int		valid_line;

	valid_line = 0;
	map->fd = open(filename, O_RDONLY);
	if (map->fd < 0 || ft_strncmp(".ber",
			&filename[ft_strlen(filename) - 4], 4))
		parsing_error();
	ret = 1;
	size = 0;
	map->height = 0;
	while (ret > 0)
		ret = file_sz(map, &size, &line, &valid_line);
	close(map->fd);
	if (valid_line == 1)
		parsing_error();
	if (!size && !map->height)
	{
		free(line);
		parsing_error();
	}
	return (size);
}

void	parsing_map(t_map *map, char *filename)
{
	char	*line;
	int		idx;
	int		ret;

	ret = 1;
	idx = -1;
	map->width = render_map(filename, map);
	if (map->width == map->height)
		parsing_error();
	map->map = (char **)malloc(sizeof(char *) * map->height);
	map->fd = open (filename, O_RDONLY);
	if (map->fd < 0 || !map->map)
		parsing_error();
	while (ret > 0)
	{
		ret = get_next_line(map->fd, &line);
		map->map[++idx] = ft_strdup(line);
		free(line);
	}
	close(map->fd);
	map->counter = 0;
	map->collect = 0;
	verif_map(map);
}
