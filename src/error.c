/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 10:45:58 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/02/13 10:54:28 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	map_error(t_map *map, int code)
{
	ft_putendl_fd("Error", 2);
	if (code == 1)
		ft_putendl_fd("usage: ./so_long map.ber", 2);
	if (code == 2)
		ft_putendl_fd("./so_long: map read failed", 2);
	if (code == 3)
		ft_putendl_fd("./so_long: map is not rectangular", 2);
	if (code == 4)
		ft_putendl_fd("./so_long: map contain invalid characters", 2);
	if (code == 5)
		ft_putendl_fd("./so_long: no such file or directory", 2);
	if (code == 6)
		ft_putendl_fd("./so_long: map must be closed/surrounded by walls", 2);
	if (code == 7)
		ft_putendl_fd(\
		"./so_long: 1 exit, 1 player and at least 1 item accepted", 2);
	if (code == 8)
		ft_putendl_fd("./so_long: all items and exit should be reachable", 2);
	if (map)
		free_map(map);
}

void	cleanup_images(t_data *data)
{
	if (data->img->wall)
		mlx_delete_image(data->mlx, data->img->wall);
	if (data->img->flr)
		mlx_delete_image(data->mlx, data->img->flr);
	if (data->img->col)
		mlx_delete_image(data->mlx, data->img->col);
	if (data->img->player_l)
		mlx_delete_image(data->mlx, data->img->player_l);
	if (data->img->player_r)
		mlx_delete_image(data->mlx, data->img->player_r);
	if (data->img->exit)
		mlx_delete_image(data->mlx, data->img->exit);
	if (data->img->exit_open)
		mlx_delete_image(data->mlx, data->img->exit_open);
	free(data->img);
}

void	game_error(t_data *data, char *msg, int code)
{
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(msg, 2);
	if (data->img)
		cleanup_images(data);
	if (data->mlx)
		mlx_terminate(data->mlx);
	if (data)
	{
		free_map(data->map);
		free(data);
	}
	exit(code);
}

void	destroy_all(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (data->img)
		cleanup_images(data);
	if (data->mlx)
		mlx_terminate(data->mlx);
	if (data->map)
		free_map(data->map);
	if (data)
		free(data);
	ft_putendl_fd("Good bye!", 1);
	exit(0);
}
