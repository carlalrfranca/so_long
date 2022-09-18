/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cleticia <cleticia@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 16:20:52 by cleticia          #+#    #+#             */
/*   Updated: 2021/10/14 16:21:17 by cleticia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

void	get_copy_line(char *bkdest, char *bksrc, size_t bksize)
{
	size_t	index;

	if (!bkdest || !bksrc)
		return ;
	index = 0;
	while (bksrc[index] && bksize && index + 1 < bksize)
	{
		bkdest[index] = bksrc[index];
		index++;
	}
	bkdest[index] = '\0';
}

int	get_cut_line(char **line, char *backup, char *buff)
{
	int	index;
	int	size_backup;

	index = 0;
	free(buff);
	while (backup[index] != '\n')
	{
		index++;
	}
	size_backup = ft_strlen(backup);
	*line = ft_substr(backup, 0, index);
	index++;
	get_copy_line(backup, backup + index, size_backup + 1);
	return (1);
}

int	get_read_file(int fd, char **line, char *buff, char **backup)
{
	int		read_bytes;
	char	*temp_backup;

	read_bytes = read(fd, buff, BUFFER_SIZE);
	while (read_bytes > 0)
	{
		buff[read_bytes] = '\0';
		if (*backup)
		{
			temp_backup = ft_strjoin(*backup, buff);
			free(*backup);
			*backup = temp_backup;
		}
		else
			*backup = ft_strdup(buff);
		if (ft_strchr(*backup, '\n'))
			return (get_cut_line(line, *backup, buff));
		else
			read_bytes = read(fd, buff, BUFFER_SIZE);
	}
	return (read_bytes);
}

void	get_bkto_line(char **line, char **backup)
{
	*line = ft_strdup(*backup);
	free(*backup);
	*backup = NULL;
}

int	get_next_line(int fd, char **line)
{
	static char	*backup;
	char		*buff;
	int			ret;

	buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (-1);
	if (fd < 0 || !line || BUFFER_SIZE < 1 || read(fd, backup, 0) < 0 )
	{
		free(buff);
		return (-1);
	}
	if (backup && ft_strchr(backup, '\n'))
		return (get_cut_line(line, backup, buff));
	ret = get_read_file(fd, line, buff, &backup);
	if (ret == 1)
		return (1);
	free(buff);
	if (backup)
	{
		get_bkto_line(line, &backup);
		return (ret);
	}
	*line = ft_strdup("");
	return (ret);
}
