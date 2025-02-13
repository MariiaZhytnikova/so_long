/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 16:32:21 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/02/12 18:25:02 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	data_init(t_data *data)
{
	int	i;
	
	data->moves = 0;
	data->hero_dir = 0;
	data->hero_frame = 0;
	data->hero_frame_count = 0;
	data->col_count = data->map->col;
	data->col_frame = 0;
	data->col_frame_count = 0;
	i = 0;
	while (i < data->map->enemy)
	{
		data->map->enemies[i].dir_x = 1;
		data->map->enemies[i].dir_y = 1;
		data->map->enemies[i].frame = 0;
		data->map->enemies[i].frame_count = 0;
		i++;
	}
}

void	img_init(t_data *data)
{
	data->img->wall = NULL;
	data->img->flr = NULL;
	data->img->exit = NULL;
	data->img->exit_open = NULL;
	data->img->moves_field = NULL;
	data->img->col[0] = NULL;
	data->img->col[1] = NULL;
	data->img->enemies[0] = NULL;
	data->img->enemies[1] = NULL;
	data->img->enemies[2] = NULL;
	data->img->player_l[0] = NULL;
	data->img->player_r[0] = NULL;
	data->img->player_l[1] = NULL;
	data->img->player_r[1] = NULL;
	data->img->player_l[2] = NULL;
	data->img->player_r[2] = NULL;
}

void	img_alloc(t_data *data)
{
	data->img = malloc(sizeof(t_img));
	if (!data->img)
		game_error(data, "Failed to allocate memory for images", 1);
	data->img->col = (mlx_image_t **)malloc(sizeof(mlx_image_t *) * 2);
	if (!data->img->col)
		game_error(data, "./so_ long: image loading failed", 1);
	data->img->player_r = (mlx_image_t **)malloc(sizeof(mlx_image_t *) * 3);
	if (!data->img->player_r)
		game_error(data, "./so_ long: image loading failed", 1);
	data->img->player_l = (mlx_image_t **)malloc(sizeof(mlx_image_t *) * 3);
	if (!data->img->player_l)
		game_error(data, "./so_ long: image loading failed", 1);
	data->img->enemies = (mlx_image_t **)malloc(sizeof(mlx_image_t *) * 3);
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
	img_init(data);
	load_images(data);
	draw_map(data);
	mlx_image_to_window(data->mlx, data->img->moves_field, 5, 3);
	mlx_put_string(data->mlx, "Moves:0", 20, 20);
	mlx_image_to_window(data->mlx, data->img->exit, data->map->exit_pos.x * 
						TS, data->map->exit_pos.y * TS);
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
