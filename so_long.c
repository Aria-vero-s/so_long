/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaulnie <asaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 19:22:39 by asaulnie          #+#    #+#             */
/*   Updated: 2024/11/10 03:19:41 by asaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#define MAP_WIDTH 18
#define MAP_HEIGHT 7
#define TILE_SIZE 32
#define W (MAP_WIDTH * TILE_SIZE)
#define H (MAP_HEIGHT * TILE_SIZE)

void	load_images(t_data *data)
{
	int		i;
	int		width;
	int		height;

	i = 0;
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

int	get_texture_index(char current_tile)
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
			texture_index = get_texture_index(map[y][x]);
			if (texture_index != -1)
				display_image(data, texture_index, x * TILE_SIZE, y * TILE_SIZE);
			x++;
		}
		y++;
	}
}

void	free_map(t_map map)
{
	int		i;

	i = 0;
	while (i < map.height)
	{
		free(map.grid[i]);
		i++;
	}
	free(map.grid);
	map.grid = NULL;
}

int	on_destroy(t_data *data)
{
	int		i;

	i = 0;
	while (i < 5)
	{
		mlx_destroy_image(data->mlx_ptr, data->textures[i]);
		i++;
	}
	free_map(data->map);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	exit(0);
}

int	handle_keypress(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		on_destroy(data);
	return (0);
}

int	render(t_data *data)
{
	if (data->map.grid)
		render_map(data, data->map.grid, data->map.width, data->map.height);
	else
		ft_printf("Map or grid is NULL!\n");
	return (0);
}

void	handle_error(char *code, t_data *data)
{
	if (code)
		ft_printf(ERR_MAP_SIZE);
	// else if (code == ERR_MULTIPLE_EXITS)
	// 	ft_printf("Error: More than one exit found in the map.\n");
	// else if (code == ERR_INVALID_CHARACTER)
	// 	ft_printf("Error: Invalid character.\n");
	// else if (code == ERR_MISSING_PLAYER)
	// 	ft_printf("Error: Missing player.\n");
	else
		ft_printf("Error: Unknown error occurred.\n");
	on_destroy(data);
}

void	initialize_grid(t_map *map, const char *filename)
{
	int		fd;
	int		i;
	char	*line;

	i = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0 || !map)
		exit(1);
	line = get_next_line(fd);
	map->grid = malloc(map->height * sizeof(char *));
	while (i < map->height)
	{
		map->grid[i] = ft_strdup(line);
		free(line);
		line = get_next_line(fd);
		i++;
	}
	close(fd);
}

void	load_map(const char *filename, t_map *map, t_data *data)
{
	size_t	line_count;
	size_t	max_width;
	int		fd;
	char	*line;

	line_count = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0 || !map)
		exit(1);
	line = get_next_line(fd);
	max_width = ft_strlen(line);
	while (line != NULL)
	{
		if (max_width != ft_strlen(line))
			handle_error(ERR_MAP_SIZE, data);
		else if (ft_strlen(line) >= max_width)
			max_width = ft_strlen(line);
		line_count++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	map->height = line_count;
	map->width = max_width;
	initialize_grid(map, filename);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc == 2)
	{
		data.mlx_ptr = mlx_init();
		if (data.mlx_ptr == NULL)
			return (1);
		data.win_ptr = mlx_new_window(data.mlx_ptr, W, H, "so_long");
		if (data.win_ptr == NULL)
			return (1);
		load_images(&data);
		load_map(argv[1], &data.map, &data);
		mlx_loop_hook(data.mlx_ptr, &render, &data);
		mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);
		mlx_hook(data.win_ptr, DestroyNotify, StructureNotifyMask, &on_destroy, &data);
		mlx_loop(data.mlx_ptr);
	}
	else
	{
		ft_printf("Error: this program needs a map.ber\n");
		return (1);
	}
	return (0);
}
