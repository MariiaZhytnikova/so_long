/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 11:56:34 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/02/15 16:11:32 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	lines_check(t_map *map)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (map->field[y])
	{
		if (y == map->size.y - 2)
			x = ft_strlen(map->field[y]) + 1;
		else
			x = ft_strlen(map->field[y]);
		if (x != map->size.x)
			return (1);
		y++;
	}
	return (0);
}

int	line_count(char *fname)
{
	int		fd;
	char	*line;
	int		count;

	fd = open(fname, O_RDONLY);
	if (fd < 0)
		return (map_error(NULL, 6), 0);
	count = 0;
	while (1)
	{
		line = get_next_line(fd);
		count++;
		if (!line)
			break ;
		free(line);
	}
	close(fd);
	return (count);
}

void	read_map(t_map *map, char *fname, int last)
{
	int		fd;
	char	*line;
	int		count;

	fd = open(fname, O_RDONLY);
	if (fd < 0)
		return (map_error(map, 6));
	count = 0;
	while (count < last)
	{
		line = get_next_line(fd);
		map->field[count] = ft_strdup(line);
		if (!line || !map->field[count])
			break ;
		free(line);
		count++;
	}
	map->size.x = ft_strlen(map->field[0]);
	close(fd);
}

int	file_check(char *file_name)
{
	return (ft_strlen(file_name) < 5 || !ft_strchr(file_name, '.') \
			|| ft_strncmp((ft_strrchr(file_name, '.')), ".ber\0", 5));
}

t_map	*get_map(int argc, char **argv)
{
	t_map	*map;
	int		code;

	if (!argv[1] || ft_strlen(argv[1]) < 5 || file_check(argv[1]) || argc > 2)
		return (map_error(NULL, 1), NULL);
	map = (t_map *)ft_calloc(1, sizeof(t_map));
	if (!map)
		return (map_error(NULL, 2), NULL);
	map->size.y = line_count(argv[1]);
	if (!map->size.y)
		return (free(map), NULL);
	if (map->size.y < 3)
		return (map_error(map, 3), NULL);
	map->field = (char **)ft_calloc(map->size.y, sizeof(char *));
	if (!map->field)
		return (map_error(map, 2), NULL);
	read_map(map, argv[1], map->size.y);
	if (!map->field[0])
		return (free(map), NULL);
	if (lines_check(map) == 1)
		return (map_error(map, 4), NULL);
	code = fill_check(map);
	if (code)
		return (map_error(map, code), NULL);
	return (map);
}
