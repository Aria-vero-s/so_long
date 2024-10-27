/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaulnie <asaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 19:22:39 by asaulnie          #+#    #+#             */
/*   Updated: 2024/10/27 19:01:10 by asaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#include <X11/X.h>
#include <X11/keysym.h>
#include <mlx.h>

#define W 600
#define H 300
#define MAP_WIDTH 18
#define MAP_HEIGHT 7
#define TILE_SIZE 32

int on_destroy(t_data *data)
{
	int		i;

	i = 0;
	while (i < 5)
	{
		mlx_destroy_image(data->mlx_ptr, data->textures[i]);
		i++;
	}
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	exit(0);
	return (0);
}

int	handle_keypress(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		data->win_ptr = NULL;
		exit (0);
	}
	return (0);
}

void	load_images(t_data *data)
{
	int		i;
	int		width;
	int		height;
	char	*error_message = "Error loading texture ";

	i = 0;
	data->textures_path[0] = "assets/chests.xpm";
	data->textures_path[1] = "assets/coconut.xpm";
	data->textures_path[2] = "assets/dolphin.xpm";
	data->textures_path[3] = "assets/portal.xpm";
	data->textures_path[4] = "assets/shore.xpm";
	while (i < 5)
	{
		data->textures[i] = mlx_xpm_file_to_image(data->mlx_ptr, data->textures_path[i], &width, &height);
		if (data->textures[i] == NULL)
		{
			write(1, error_message, ft_strlen(error_message));
			write(1, data->textures_path, ft_strlen(data->textures_path[i]));
			write(1, "\n", 1);
			exit (1);
		}
		i++;
	}
}

void	display_image(t_data *data, int index, int x, int y)
{
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->textures[index], x, y);
}

int	render(t_data *data)
{
	data = 0;
	data++;
	data--;
	return (0);
}

void load_map(const char *filename, t_map *map)
{
	int fd = open(filename, O_RDONLY);
	if (fd == -1)
		exit(1);
	char *line;
	int line_count = 0;
	size_t max_width = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		line_count++;
		size_t line_length = ft_strlen(line);
		if (line_length > max_width)
			max_width = line_length;
		free(line);
	}
	close(fd);
	map->height = line_count;
	map->width = max_width;
	map->grid = malloc(map->height * sizeof(char *));
	int		i;

	i = 0;
	while (i < map->height)
	{
		map->grid[i] = malloc(map->width * sizeof(char));
		memset(map->grid[i], '0', map->width);
		i++;
	}
	if (!map->grid)
		exit(1);
	int		j;

	j = 0;
	while (j < map->height)
	{
		map->grid[j] = malloc(sizeof(char) * (map->width + 1));
		if (!map->grid[j])
			exit(1);
		j++;
	}

	fd = open(filename, O_RDONLY);
	if (fd == -1) {
		perror("Error opening map file");
		exit(1);
	}

	i = 0;
	while ((line = get_next_line(fd)) && i < map->height)
	{
		int		j;

		j = 0;
		while (j < (int)ft_strlen(line) && j < (int)map->width)
		{
			if (line[j] == '\0' || line[j] == '\n')
				break;
			map->grid[i][j] = line[j];
			j++;
		}
		map->grid[i][ft_strlen(line)] = '\0';
		free(line);
		i++;
	}

	close(fd);
}

void render_map(t_data *data, char **map, int width, int height)
{
	int		y;

	y = 0;
	while (y < height)
	{
		int		x;

		x = 0;
		while (x < width)
		{
			char current_tile = map[y][x];
			if (current_tile != '\0')
			{
				int texture_index = -1;
				if (current_tile == '1')
					texture_index = 0;
				else if (current_tile == '0')
					texture_index = 1;
				if (texture_index != -1)
					display_image(data, texture_index, x * TILE_SIZE, y * TILE_SIZE);
			}
			x++;
		}
		y++;
	}
}


void free_map(t_map *map)
{
	int		i;

	i = 0;
	while (i < map->height)
	{
		free(map->grid[i]);
		i++;
	}
	free(map->grid);
	map->grid = NULL;
}

int main(int argc, char **argv)
{
	if (argc == 2)
	{
		t_data	data;
		t_map	map;

		data.mlx_ptr = mlx_init();
		if (data.mlx_ptr == NULL)
			return (1);
		data.win_ptr = mlx_new_window(data.mlx_ptr, W, H, "so_long");
		if (data.win_ptr == NULL)
			return (1);
		load_images(&data);
		load_map(argv[1], &map);
		render_map(&data, map.grid, map.width, map.height);
		free_map(&map);
		mlx_loop_hook(data.mlx_ptr, &render, &data);
		mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);
		mlx_hook(data.win_ptr, DestroyNotify, StructureNotifyMask, &on_destroy, &data);
		mlx_loop(data.mlx_ptr);
	}
	else
		return (1);
	return (0);
}
