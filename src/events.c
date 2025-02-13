/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 17:36:22 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/02/13 10:59:43 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check_wall(t_data *data, int new_x, int new_y)
{
	char	*moves;

	if (data->map->field[new_y][new_x] != '1')
	{
		data->map->pos.x = new_x;
		data->map->pos.y = new_y;
		data->moves++;
		moves = ft_itoa(data->moves);
		ft_putstr_fd("Moves: ", 1);
		ft_putstr_fd(moves, 1);
		ft_putstr_fd("\n", 1);
		free(moves);
	}
}

void	check_collectible(t_data *data, int new_x, int new_y)
{
	int	i;

	i = 0;
	if (data->map->field[new_y][new_x] == 'C')
	{
		data->map->col--;
		data->map->field[new_y][new_x] = '0';
		if (data->map->col == 0)
		{
			mlx_image_to_window(data->mlx, data->img->exit_open, \
			data->map->exit_pos.x * TS, data->map->exit_pos.y * TS);
			ft_putendl_fd("It\'s time to get out!", 1);
		}
	}
}

void	event_player(t_data *data, int new_x, int new_y)
{
	if (new_x >= 0 && new_x < data->map->size.x - 1 && new_y >= 0
		&& new_y < data->map->size.y - 1)
	{
		check_wall(data, new_x, new_y);
		check_collectible(data, new_x, new_y);
		if (data->map->field[new_y][new_x] == 'E' && data->map->col == 0)
		{
			ft_putendl_fd("You reached the exit!", 1);
			destroy_all(data);
		}
	}
}

void	move_player(mlx_key_data_t key_data, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (key_data.key == MLX_KEY_ESCAPE && key_data.action == MLX_PRESS)
		destroy_all(data);
	if ((key_data.key == MLX_KEY_W || key_data.key == MLX_KEY_UP)
		&& key_data.action == MLX_PRESS)
		event_player(data, data->map->pos.x, data->map->pos.y - 1);
	if ((key_data.key == MLX_KEY_S || key_data.key == MLX_KEY_DOWN)
		&& key_data.action == MLX_PRESS)
		event_player(data, data->map->pos.x, data->map->pos.y + 1);
	if ((key_data.key == MLX_KEY_A || key_data.key == MLX_KEY_LEFT)
		&& key_data.action == MLX_PRESS)
	{
		event_player(data, data->map->pos.x - 1, data->map->pos.y);
		data->hero_dir = 1;
	}
	if ((key_data.key == MLX_KEY_D || key_data.key == MLX_KEY_RIGHT)
		&& key_data.action == MLX_PRESS)
	{
		event_player(data, data->map->pos.x + 1, data->map->pos.y);
		data->hero_dir = 0;
	}
}
