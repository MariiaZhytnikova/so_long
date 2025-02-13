/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_instances.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 19:57:21 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/02/13 10:52:09 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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

	y = 0;
	while (y < data->map->size.y - 1)
	{
		x = 0;
		while (x < data->map->size.x - 1)
		{
			if (data->map->field[y][x] == 'C')
				mlx_image_to_window(data->mlx, data->img->col, x * TS, y * TS);
			x++;
		}
		y++;
	}
}

void	draw_hero(t_data *data)
{
	mlx_image_to_window(data->mlx, data->img->player_l, \
		data->map->pos.x * TS, data->map->pos.y * TS);
	data->img->player_l->instances->enabled = false;
	mlx_image_to_window(data->mlx, data->img->player_r, \
		data->map->pos.x * TS, data->map->pos.y * TS);
	data->img->player_r->instances->enabled = true;
}
