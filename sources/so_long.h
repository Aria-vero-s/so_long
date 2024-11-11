/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaulnie <asaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 21:56:20 by asaulnie          #+#    #+#             */
/*   Updated: 2024/11/11 12:47:34 by asaulnie         ###   ########.fr       */
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
# define MAP_WIDTH 18
# define MAP_HEIGHT 7
# define TILE_SIZE 32
# define W (MAP_WIDTH * TILE_SIZE)
# define H (MAP_HEIGHT * TILE_SIZE)

// # define ERR_MULTIPLE_EXITS "Error: More than one exit found in the map."
// # define ERR_MAP_INV "Error: Invalid character."
// # define ERR_NO_P "Error: Missing player."
# define ERR_ARG 1
# define ERR_MAP_SIZE 2
# define ERR_NO_MAP 3

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
	void	*textures_path[5];
	t_map	map;
}	t_data;

void	ft_check_arg(int argc, t_data *data);
void	load_images(t_data *data);
void	display_image(t_data *data, int i, int x, int y);
int		get_texture_index(char current_tile);
void	render_map(t_data *data, char **map, int width, int height);
void	ft_handle_error(int code, t_data *data);

#endif
