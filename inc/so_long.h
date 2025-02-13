/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 14:21:02 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/02/13 10:40:46 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../lib/MLX42/include/MLX42/MLX42.h"
# include "libft.h"
# include <fcntl.h>

# define TS 64
# define WALL "./textures/64/wall.png"
# define FLOOR "./textures/64/floor.png"
# define COL1 "./textures/64/col-1.png"
# define EXIT "./textures/64/exit.png"
# define EXIT_OPEN "./textures/64/exit_open.png"
# define HERO_L1 "./textures/64/hero_l-1.png"
# define HERO_R1 "./textures/64/hero_r-1.png"
# define ENEM1 "./textures/64/enemy-1.png"

typedef struct s_point {
	int x;
	int y;
} t_point;


typedef struct s_map {
	char **field;
	t_point pos;
	t_point exit_pos;
	t_point size;
	int col;
	int exit;
	int hero;
} t_map;

typedef struct s_img
{
	mlx_image_t	*wall;
	mlx_image_t	*flr;
	mlx_image_t	*col;
	mlx_image_t	*exit;
	mlx_image_t	*exit_open;
	mlx_image_t	*player_l;
	mlx_image_t	*player_r;
} t_img;


typedef struct s_data
{
	mlx_t	*mlx;
	t_img	*img;
	t_map	*map;
	int		moves;
	int		hero_dir;
	int		col_count;
}	t_data;

void		free_map(t_map *map);
void		map_error(t_map *map, int code);
void		game_error(t_data *data, char *msg, int code);
t_map		*get_map(int argc, char **argv);
int			fill_check(t_map *map);
void		fill_pos(t_map *map);
void		flood_check(t_map *map, int x, int y, t_point *content);

void		init_mlx(t_data *data);
mlx_image_t	*load_texture(t_data *data, const char *path);
void		draw_map(t_data *data);
void		draw_col(t_data *data);
void		draw_hero(t_data *data);

void		animate_hero(void *param);
void		animate_col(void *param);
void		animate_floor(void *param);

void		move_player(mlx_key_data_t key_data, void *param);

void		destroy_all(void *param);

#endif