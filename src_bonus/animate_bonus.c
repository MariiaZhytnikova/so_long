/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animate_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 19:14:27 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/02/12 18:23:18 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	update_col(t_data *data, int i)
{
	int		old_frame;
	int		new_frame;

	old_frame = data->col_frame;
	new_frame = (old_frame + 1) % 2;
	data->img->col[old_frame]->instances[i].enabled = false;
	data->img->col[new_frame]->instances[i].enabled = true;
	data->col_frame = new_frame;
	data->col_frame_count = 0;
}

void	animate_col(void *param)
{
	t_data	*data;
	int		i;

	data = (t_data *)param;
	i = 0;
	while (i < data->col_count)
	{
		if (data->map->field[data->img->col[0]->instances[i].y / TS] \
			[data->img->col[0]->instances[i].x / TS] == 'C')
		{
			if (data->col_frame_count >= FRAME_DELAY_COL)
				update_col(data, i);
			else
				data->col_frame_count++;
		}
		else
		{
			data->img->col[1]->instances[i].enabled = false;
			data->img->col[0]->instances[i].enabled = false;
		}
		i++;
	}
}

void	animate_hero(void *param)
{
	t_data	*data;
	int		old_frame;
	int		new_frame;

	data = (t_data *)param;
	if (data->hero_frame_count >= FRAME_DELAY)
	{
		old_frame = data->hero_frame;
		new_frame = (old_frame + 1) % 3;
		if (data->hero_dir == 0)
		{
			data->img->player_r[old_frame]->instances->enabled = false;
			data->img->player_r[new_frame]->instances->enabled = true;
		}
		if (data->hero_dir == 1)
		{
			data->img->player_l[old_frame]->instances->enabled = false;
			data->img->player_l[new_frame]->instances->enabled = true;
		}
		data->hero_frame = new_frame;
		data->hero_frame_count = 0;
	}
	else
		data->hero_frame_count++;
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

void	animate_enemy(void *param)
{
	t_data	*data;
	int		i;
	int		old_frame;
	int		new_frame;

	data = (t_data *)param;
	i = 0;
	while (i < data->map->enemy)
	{
		if (data->map->enemies[i].frame_count >= FRAME_DELAY)
		{
			old_frame = data->map->enemies[i].frame;
			new_frame = (old_frame + 1) % 3;
			data->img->enemies[old_frame]->instances[i].enabled = false;
			data->img->enemies[new_frame]->instances[i].enabled = true;
			data->map->enemies[i].frame = new_frame;
			data->map->enemies[i].frame_count = 0;
		}
		else
			data->map->enemies[i].frame_count++;
		i++;
	}
}
