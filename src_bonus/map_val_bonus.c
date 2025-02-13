/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_val_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:45:52 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/02/12 18:24:58 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	free_map(t_map *map)
{
	int	i;

	i = 0;
	if (map->field)
	{
		while (map->field[i])
			free(map->field[i++]);
		free(map->field);
	}
	if (map->enemy > 0)
		free(map->enemies);
	if (map)
		free(map);
}

void	copy_map(t_map *copy, t_map *map)
{
	int	y;

	copy->field = (char **)malloc(sizeof(char *) * map->size.y);
	if (!copy->field)
		return ;
	copy->size.x = map->size.x;
	copy->size.y = map->size.y;
	copy->pos.x = map->pos.x;
	copy->pos.y = map->pos.y;
	copy->enemy = 0;
	y = 0;
	while (map->field[y])
	{
		copy->field[y] = ft_strdup(map->field[y]);
		if (!copy->field[y])
		{
			copy->field = NULL;
			return (free_map(copy));
		}
		y++;
	}
	copy->field[y] = NULL;
}

int	boder_check(t_map *map)
{
	t_point	pos;
	int		ind;

	pos.y = 0;
	while (pos.y < map->size.y - 2)
	{
		if (map->field[pos.y][0] != '1' ||
			map->field[pos.y][map->size.x - 2] != '1')
			return (1);
		pos.y++;
	}
	ind = 0;
	pos.x = 0;
	while (map->field[ind][pos.x])
	{
		if (map->field[ind][pos.x] != '1' && map->field[ind][pos.x] != '\n')
			return (1);
		pos.x++;
		if (pos.x == map->size.x)
		{
			ind = map->size.y - 2;
			pos.x = 0;
		}
	}
	return (0);
}

int	char_check(t_map *map)
{
	int	y;
	int	x;

	y = 0;
	while (map->field[y])
	{
		x = 0;
		while (x < map->size.x - 2)
		{
			if (map->field[y][x] != '0' && map->field[y][x] != '1' &&
			map->field[y][x] != 'C' && map->field[y][x] != 'E' &&
			map->field[y][x] != 'P' && map->field[y][x] != 'A')
				return (1);
			x++;
		}
		y++;
	}
	return (0);
}

int	fill_check(t_map *map)
{
	t_point	content;
	t_map	*copy;

	fill_pos(map);
	if (char_check(map))
		return (4);
	if (boder_check(map) == 1)
		return (6);
	if (!(map->hero == 1 && map->exit == 1 && map->col > 0))
		return (7);
	content.x = map->col;
	content.y = map->exit;
	copy = (t_map *)malloc(sizeof(t_map));
	copy_map(copy, map);
	if (!copy->field || !copy->field[0])
		return (2);
	flood_check(copy, copy->pos.x, copy->pos.y, &content);
	free_map(copy);
	if (content.x > 0 || content.y > 0)
		return (8);
	if (map->enemy > 0 && (map->size.x - 1)
		* (map->size.y - 1) / map->enemy < 6)
		return (9);
	return (0);
}
