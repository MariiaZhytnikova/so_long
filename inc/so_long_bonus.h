/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 14:21:02 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/02/15 15:57:45 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_BONUS_H
# define SO_LONG_BONUS_H

# include "../lib/MLX42/include/MLX42/MLX42.h"
# include "libft.h"
# include <fcntl.h>

# define FRAME_DELAY 10
# define FRAME_DELAY_COL 30
# define TS 64
# define WALL "./textures/wall.png"
# define FLOOR "./textures/floor.png"
# define COL1 "./textures/col-1.png"
# define COL2 "./textures/col-2.png"
# define EXIT "./textures/exit.png"
# define EXIT_OPEN "./textures/exit_open.png"
# define HERO_L1 "./textures/hero_l-1.png"
# define HERO_R1 "./textures/hero_r-1.png"
# define HERO_L2 "./textures/hero_l-2.png"
# define HERO_R2 "./textures/hero_r-2.png"
# define HERO_L3 "./textures/hero_l-3.png"
# define HERO_R3 "./textures/hero_r-3.png"
# define MOVES "./textures/moves.png"
# define ENEM1 "./textures/enemy-1.png"
# define ENEM2 "./textures/enemy-2.png"
# define ENEM3 "./textures/enemy-3.png"

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_enemies
{
	int	x;
	int	y;
	int	dir_x;
	int	dir_y;
	int	frame;
	int	frame_count;
}	t_enemies;

typedef struct s_map
{
	char		**field;
	t_point		pos;
	t_point		exit_pos;
	t_point		size;
	int			col;
	int			exit;
	int			hero;
	int			enemy;
	t_enemies	*enemies;
}	t_map;

typedef struct s_img
{
	mlx_image_t	*wall;
	mlx_image_t	*flr;
	mlx_image_t	**col;
	mlx_image_t	*exit;
	mlx_image_t	*exit_open;
	mlx_image_t	**player_l;
	mlx_image_t	**player_r;
	mlx_image_t	**enemies;
	mlx_image_t	*moves_field;
}	t_img;

typedef struct s_data
{
	mlx_t	*mlx;
	t_img	*img;
	t_map	*map;
	int		moves;
	int		hero_dir;
	int		hero_frame;
	int		hero_frame_count;
	int		col_count;
	int		col_frame;
	int		col_frame_count;
	int		width;
	int		height;
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
void		draw_enemy(t_data *data, int i);

void		animate_enemy(void *param);
void		animate_hero(void *param);
void		animate_col(void *param);
void		animate_floor(void *param);

void		enemy_move(t_data *data);
void		check_enemy(t_data *data);
void		move_player(mlx_key_data_t key_data, void *param);

void		destroy_all(void *param);

#endif
