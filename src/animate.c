/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animate.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 19:14:27 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/02/13 11:07:53 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	animate_col(void *param)
{
	t_data	*data;
	int		i;

	data = (t_data *)param;
	i = 0;
	while (i < data->col_count)
	{
		if (data->map->field[data->img->col->instances[i].y / TS] \
			[data->img->col->instances[i].x / TS] == 'C')
			data->img->col->instances[i].enabled = true;
		else
			data->img->col->instances[i].enabled = false;
		i++;
	}
}

void	animate_hero(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (data->hero_dir == 0)
	{
		data->img->player_r->instances->x = data->map->pos.x * TS;
		data->img->player_r->instances->y = data->map->pos.y * TS;
		data->img->player_r->instances->enabled = true;
		data->img->player_l->instances->enabled = false;
	}
	else if (data->hero_dir == 1)
	{
		data->img->player_l->instances->x = data->map->pos.x * TS;
		data->img->player_l->instances->y = data->map->pos.y * TS;
		data->img->player_l->instances->enabled = true;
		data->img->player_r->instances->enabled = false;
	}
}

void	animate_floor(void *param)
{
	t_data	*data;
	int		x;
	int		y;
	int		i;

	data = (t_data *)param;
	y = 0;
	i = 0;
	while (y < data->map->size.y - 1)
	{
		x = 0;
		while (x < data->map->size.x - 1)
		{
			if (data->map->field[y][x] != '1')
			{
				data->img->flr->instances[i].x = x * TS;
				data->img->flr->instances[i].y = y * TS;
				i++;
			}
			x++;
		}
		y++;
	}
}
