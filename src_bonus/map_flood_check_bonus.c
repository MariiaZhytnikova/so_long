/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_flood_check_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 09:39:51 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/02/15 13:08:56 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	count(t_map *map, char c)
{
	int	count;
	int	y;
	int	x;

	count = 0;
	y = 0;
	while (map->field[y])
	{
		x = 0;
		while (map->field[y][x])
		{
			if (map->field[y][x] == c)
				count++;
			x++;
		}
		y++;
	}
	return (count);
}

void	get_position(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (map->field[y])
	{
		x = 0;
		while (map->field[y][x])
		{
			if (map->field[y][x] == 'P')
			{
				map->pos.x = x;
				map->pos.y = y;
			}
			if (map->field[y][x] == 'E')
			{
				map->exit_pos.x = x;
				map->exit_pos.y = y;
			}
			x++;
		}
		y++;
	}
}

void	enemy_pos(t_map *map)
{
	int	ind;
	int	y;
	int	x;

	ind = 0;
	y = 0;
	while (map->field[y])
	{
		x = 0;
		while (map->field[y][x])
		{
			if (map->field[y][x] == 'A')
			{
				map->enemies[ind].x = x;
				map->enemies[ind].y = y;
				ind++;
			}
			x++;
		}
		y++;
	}
}

void	fill_pos(t_map *map)
{
	map->hero = count(map, 'P');
	map->col = count(map, 'C');
	map->exit = count(map, 'E');
	map->enemy = count(map, 'A');
	get_position(map);
	if (map->enemy > 0)
	{
		map->enemies = (t_enemies *)ft_calloc((map->enemy), \
						sizeof(t_enemies));
		if (!map->enemies)
			return (map_error(map, 2));
		enemy_pos(map);
	}
}

void	flood_check(t_map *map, int x, int y, t_point *content)
{
	if (map->field[y][x] == 'E')
		content->y -= 1;
	if (map->field[y][x] == 'C')
		content->x -= 1;
	map->field[y][x] = '1';
	if (y > 0 && map->field[y - 1][x] != '1' && map->field[y - 1][x] != 'A')
		flood_check(map, x, y - 1, content);
	if (y < (map->size.y - 2) && map->field[y + 1][x] != '1'
			&& map->field[y + 1][x] != 'A')
		flood_check(map, x, y + 1, content);
	if (x < (map->size.x - 2) && map->field[y][x + 1] != '1'
			&& map->field[y][x + 1] != 'A')
		flood_check(map, x + 1, y, content);
	if (x > 0 && map->field[y][x - 1] != '1' && map->field[y][x - 1] != 'A')
		flood_check(map, x - 1, y, content);
}
