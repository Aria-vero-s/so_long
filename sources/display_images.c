/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_images.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaulnie <asaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 18:24:54 by asaulnie          #+#    #+#             */
/*   Updated: 2024/11/20 17:40:42 by asaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	load_images(t_data *data)
{
	int		i;
	int		width;
	int		height;

	i = 0;
	width = 32;
	height = 32;
	data->textures_path[0] = "assets/chest.xpm";
	data->textures_path[1] = "assets/wall.xpm";
	data->textures_path[2] = "assets/player.xpm";
	data->textures_path[3] = "assets/exit.xpm";
	data->textures_path[4] = "assets/empty.xpm";
	while (i < 5)
	{
		data->textures[i] = mlx_xpm_file_to_image(data->mlx_ptr, data->textures_path[i], &width, &height);
		if (data->textures[i] == NULL)
			exit (1);
		i++;
	}
}

void	display_image(t_data *data, int i, int x, int y)
{
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->textures[i], x, y);
}

int	get_texture_index(char current_tile, t_data *data)
{
	if (current_tile == 'C')
		return (0);
	else if (current_tile == '1')
		return (1);
	else if (current_tile == 'P')
		return (2);
	else if (current_tile == 'E')
		return (3);
	else if (current_tile == '0')
		return (4);
	else if (current_tile != '\n')
		handle_error(ERR_INV_CHAR, data);
	return (-1);
}

void	render_map(t_data *data, char **map, int width, int height)
{
	int	y;
	int	x;
	int	texture_index;

	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			texture_index = get_texture_index(map[y][x], data);
			if (texture_index != -1)
				display_image(data, texture_index, x * TILE_SIZE, y * TILE_SIZE);
			x++;
		}
		y++;
	}
}
