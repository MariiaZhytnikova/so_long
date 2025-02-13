/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_instances_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 19:57:21 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/02/12 18:23:28 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

mlx_image_t	*load_texture(t_data *data, const char *path)
{
	mlx_texture_t	*texture;
	mlx_image_t		*image;

	texture = mlx_load_png(path);
	if (!texture)
		game_error(data, "./so_ long: image loading failed", 1);
	image = mlx_texture_to_image(data->mlx, texture);
	if (!image)
		game_error(data, "./so_ long: image loading failed", 1);
	mlx_delete_texture(texture);
	return (image);
}

void	draw_map(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->map->size.y - 1)
	{
		x = 0;
		while (x < data->map->size.x - 1)
		{
			if (data->map->field[y][x] == '1')
				mlx_image_to_window(data->mlx, data->img->wall, x * TS, y * TS);
			else
				mlx_image_to_window(data->mlx, data->img->flr, x * TS, y * TS);
			x++;
		}
		y++;
	}
}

void	draw_col(t_data *data)
{
	int	x;
	int	y;
	int	frame;

	y = 0;
	while (y < data->map->size.y - 1)
	{
		x = 0;
		while (x < data->map->size.x - 1)
		{
			if (data->map->field[y][x] == 'C')
			{
				frame = 0;
				while (frame < 2)
				{
					mlx_image_to_window(data->mlx, data->img->col[frame], \
						x * TS, y * TS);
					data->img->col[frame]->instances->enabled = (frame == 0);
					frame++;
				}
			}
			x++;
		}
		y++;
	}
}

void	draw_hero(t_data *data)
{
	int	frame;

	frame = 0;
	while (frame < 3)
	{
		mlx_image_to_window(data->mlx, data->img->player_l[frame], \
			data->map->pos.x * TS, data->map->pos.y * TS);
		data->img->player_l[frame]->instances->enabled = false;
		frame++;
	}
	frame = 0;
	while (frame < 3)
	{
		mlx_image_to_window(data->mlx, data->img->player_r[frame], \
			data->map->pos.x * TS, data->map->pos.y * TS);
		data->img->player_r[frame]->instances->enabled = (frame == 0);
		frame++;
	}
}

void	draw_enemy(t_data *data, int i)
{
	int	frame;

	frame = 0;
	while (frame < 3)
	{
		mlx_image_to_window(data->mlx, data->img->enemies[frame], \
			data->map->enemies[i].x * TS, data->map->enemies[i].y * TS);
		data->img->enemies[frame]->instances[i].enabled = (frame == 0);
		frame++;
	}
}
