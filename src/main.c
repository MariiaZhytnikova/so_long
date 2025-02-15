/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 10:16:52 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/02/15 15:53:50 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char **argv)
{
	t_data	*data;

	data = (t_data *)ft_calloc(1, sizeof(t_data));
	if (!data)
		return (1);
	data->map = get_map(argc, argv);
	if (!data->map || !data->map->field)
	{
		free(data);
		exit (1);
	}
	init_mlx(data);
	mlx_get_monitor_size(0, &data->width, &data->height);
	if (data->map->size.x * TS >= data->width || data->map->size.y * \
		TS >= data->height)
		game_error(data, "./so_ long: map is too big", 1);
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	mlx_close_hook(data->mlx, destroy_all, data);
	mlx_loop_hook(data->mlx, animate_floor, data);
	mlx_loop_hook(data->mlx, animate_col, data);
	mlx_loop_hook(data->mlx, animate_hero, data);
	mlx_key_hook(data->mlx, move_player, data);
	mlx_loop(data->mlx);
	return (0);
}
