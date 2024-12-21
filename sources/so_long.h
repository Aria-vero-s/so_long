/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaulnie <asaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 21:56:20 by asaulnie          #+#    #+#             */
/*   Updated: 2024/12/21 18:13:58 by asaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <mlx.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include "libft.h"
# include "../get_next_line/get_next_line.h"
# include "../ft_printf/ft_printf.h"
# define TILE_SIZE 32
# define ERR_ARG 1
# define ERR_MAP_SIZE 2
# define ERR_NO_MAP 3
# define ERR_INV_CHAR 4
# define ERR_EMPTY 5
# define ERR_MISSING_W 6
# define ERR_NOT_POSS 7
# define ERR_MULTI_P 8
# define ERR_MULTI_E 9
# define ERR_NO_P 10
# define ERR_NO_E 11
# define ERR_NO_C 12
# define ERR_EXT 13
# define ERR_MAP_BIG 14
# define ERR_NO_IMG 25
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_map
{
	int		width;
	int		height;
	char	**grid;
}	t_map;

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*textures[5];
	void	*path[5];
	t_map	map;
	int		player_x;
	int		player_y;
	int		total_chests;
	int		collected_count;
	int		steps;
}	t_data;

typedef struct s_fill_params
{
	int		*player;
	int		*exit;
	t_data	*data;
}	t_fill_params;

int		render(t_data *data);
int		handle_keypress(int key, t_data *data);
int		on_destroy(t_data *data, int exit_status);
void	check_arg(int argc, char **argv, t_data *data);
void	load_images(t_data *data);
void	display_image(t_data *data, int i, int x, int y);
int		get_texture_index(char current_tile, t_data *data);
void	render_map(t_data *data, char **map, int width, int height);
void	handle_error(int code, t_data *data);
void	handle_error2(int code, t_data *data);
void	load_map(const char *filename, t_data *data);
void	load_map_dimensions(int fd, t_data *data);
void	initialize_grid(t_data *data, const char *filename);
void	flood_fill(char **tab, int x, int y, t_data *data);
void	fill(char **tab, t_fill_params *params, int x, int y);
void	check_player(t_data *data);
void	check_exit(t_data *data);
void	data_setter(t_data *data);

void	find_player_start(t_data *data);
void	move_player(t_data *data, int new_x, int new_y);
void	draw_tile(t_data *data, int x, int y);
void	free_map_copy(char **copy, int height);
char	**copy_map(char **tab, int height);
void	count_collectibles(t_data *data);
int		is_valid_move(t_data *data, int x, int y);
void	check_map_size(t_data *data, int map_width, int map_height);

#endif
