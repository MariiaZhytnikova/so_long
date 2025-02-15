/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 16:32:21 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/02/15 13:05:29 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	data_init(t_data *data)
{
	int	i;

	data->col_count = data->map->col;
	i = 0;
	while (i < data->map->enemy)
	{
		data->map->enemies[i].dir_x = 1;
		data->map->enemies[i].dir_y = 1;
		i++;
	}
}

void	img_alloc(t_data *data)
{
	data->img = ft_calloc(1, sizeof(t_img));
	if (!data->img)
		game_error(data, "Failed to allocate memory for images", 1);
	data->img->col = (mlx_image_t **)ft_calloc(2, sizeof(mlx_image_t *));
	if (!data->img->col)
		game_error(data, "./so_ long: image loading failed", 1);
	data->img->player_r = (mlx_image_t **)ft_calloc(3, sizeof(mlx_image_t *));
	if (!data->img->player_r)
		game_error(data, "./so_ long: image loading failed", 1);
	data->img->player_l = (mlx_image_t **)ft_calloc(3, sizeof(mlx_image_t *));
	if (!data->img->player_l)
		game_error(data, "./so_ long: image loading failed", 1);
	data->img->enemies = (mlx_image_t **)ft_calloc(3, sizeof(mlx_image_t *));
	if (!data->img->enemies)
		game_error(data, "./so_ long: image loading failed", 1);
}

void	load_images(t_data *data)
{
	data->img->wall = load_texture(data, WALL);
	data->img->flr = load_texture(data, FLOOR);
	data->img->exit = load_texture(data, EXIT);
	data->img->exit_open = load_texture(data, EXIT_OPEN);
	data->img->moves_field = load_texture(data, MOVES);
	data->img->col[0] = load_texture(data, COL1);
	data->img->col[1] = load_texture(data, COL2);
	data->img->enemies[0] = load_texture(data, ENEM1);
	data->img->enemies[1] = load_texture(data, ENEM2);
	data->img->enemies[2] = load_texture(data, ENEM3);
	data->img->player_l[0] = load_texture(data, HERO_L1);
	data->img->player_r[0] = load_texture(data, HERO_R1);
	data->img->player_l[1] = load_texture(data, HERO_L2);
	data->img->player_r[1] = load_texture(data, HERO_R2);
	data->img->player_l[2] = load_texture(data, HERO_L3);
	data->img->player_r[2] = load_texture(data, HERO_R3);
}

void	init_mlx(t_data *data)
{
	int	i;

	data->mlx = mlx_init(TS * (data->map->size.x - 1), TS * \
						(data->map->size.y - 1), "So long", true);
	if (!data->mlx)
		game_error(data, "./so_long: mlx failed", 2);
	img_alloc(data);
	load_images(data);
	draw_map(data);
	mlx_image_to_window(data->mlx, data->img->moves_field, 5, 3);
	mlx_put_string(data->mlx, "Moves:0", 20, 20);
	mlx_image_to_window(data->mlx, data->img->exit, data->map->exit_pos.x \
						* TS, data->map->exit_pos.y * TS);
	data_init(data);
	draw_col(data);
	draw_hero(data);
	i = 0;
	while (i < data->map->enemy)
	{
		draw_enemy(data, i);
		i++;
	}
}
