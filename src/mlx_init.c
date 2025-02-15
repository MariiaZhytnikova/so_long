/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 16:32:21 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/02/15 12:44:22 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	load_images(t_data *data)
{
	data->img = ft_calloc(1, sizeof(t_img));
	if (!data->img)
		game_error(data, "Failed to allocate memory for images", 1);
	data->img->wall = load_texture(data, WALL);
	data->img->flr = load_texture(data, FLOOR);
	data->img->exit = load_texture(data, EXIT);
	data->img->exit_open = load_texture(data, EXIT_OPEN);
	data->img->col = load_texture(data, COL1);
	data->img->player_l = load_texture(data, HERO_L1);
	data->img->player_r = load_texture(data, HERO_R1);
}

void	init_mlx(t_data *data)
{
	int	i;

	data->mlx = mlx_init(TS * (data->map->size.x - 1), TS * \
						(data->map->size.y - 1), "So long", true);
	if (!data->mlx)
		game_error(data, "./so_long: mlx failed", 2);
	load_images(data);
	draw_map(data);
	mlx_image_to_window(data->mlx, data->img->exit, data->map->exit_pos.x \
						* TS, data->map->exit_pos.y * TS);
	data->col_count = data->map->col;
	draw_col(data);
	draw_hero(data);
	i = 0;
}
