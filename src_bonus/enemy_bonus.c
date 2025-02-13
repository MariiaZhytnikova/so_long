/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 12:52:11 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/02/12 18:23:35 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	odd_enemy_move(t_data *data, int i)
{
	if (data->map->field[data->map->enemies[i].y \
			+ data->map->enemies[i].dir_y][data->map->enemies[i].x] == '1')
		data->map->enemies[i].dir_y *= -1;
	else
		data->map->enemies[i].y += data->map->enemies[i].dir_y;
}

void	even_enemy_move(t_data *data, int i)
{
	if (data->map->field[data->map->enemies[i].y][data->map->enemies[i].x \
		+ data->map->enemies[i].dir_x] == '1')
		data->map->enemies[i].dir_x *= -1;
	else
		data->map->enemies[i].x += data->map->enemies[i].dir_x;
}

void	enemy_move(t_data *data)
{
	int	i;
	int	frame;

	i = 0;
	check_enemy(data);
	while (i < data->map->enemy)
	{
		if ((i + 1) % 2 == 0)
			odd_enemy_move(data, i);
		else
			even_enemy_move(data, i);
		frame = 0;
		while (frame < 3)
		{
			data->img->enemies[frame]->instances[i].x = \
			data->map->enemies[i].x * TS;
			data->img->enemies[frame]->instances[i].y = \
			data->map->enemies[i].y * TS;
			frame++;
		}
		i++;
	}
}

void	check_enemy(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->map->enemy)
	{
		if (data->map->pos.x == data->map->enemies[i].x
			&& data->map->pos.y == data->map->enemies[i].y)
		{
			ft_putendl_fd("You are DEAD now! Bwa-ha-ha! Try again!", 1);
			destroy_all(data);
		}
		i++;
	}
}
