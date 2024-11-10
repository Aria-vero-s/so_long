/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaulnie <asaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 19:22:39 by asaulnie          #+#    #+#             */
/*   Updated: 2024/11/10 19:22:36 by asaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	initialize_grid(t_data *data, const char *filename)
{
	int		fd;
	int		i;
	char	*line;

	i = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0 || !data)
		exit(1);
	line = get_next_line(fd);
	data->map.grid = malloc(data->map.height * sizeof(char *));
	while (i < data->map.height)
	{
		data->map.grid[i] = ft_strdup(line);
		free(line);
		line = get_next_line(fd);
		i++;
	}
	close(fd);
}

void	load_map(const char *filename, t_data *data)
{
	size_t	line_count;
	size_t	max_width;
	int		fd;
	char	*line;

	line_count = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0 || !data)
		exit(1);
	line = get_next_line(fd);
	max_width = ft_strlen(line);
	while (line != NULL)
	{
		// if (max_width != ft_strlen(line))
		// 	// handle_error(1, ERR_MAP_SIZE, data);
		if (ft_strlen(line) >= max_width)
			max_width = ft_strlen(line);
		line_count++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	data->map.height = line_count;
	data->map.width = max_width;
	initialize_grid(data, filename);
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

int	on_destroy(t_data *data, int exit_status)
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
	exit(exit_status);
}

int	handle_keypress(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		on_destroy(data, 0);
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

void	ft_handle_error(int code, t_data *data)
{
	if (code == ERR_ARG)
		ft_printf("%s\n", "Error: Not enough arguments.");
	else
		ft_printf("Error: Unknown error occurred.\n");
	on_destroy(data, 1);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	data->mlx_ptr = mlx_init();
	if (data->mlx_ptr == NULL)
		return (1);
	data->win_ptr = mlx_new_window(data->mlx_ptr, W, H, "so_long");
	if (data->win_ptr == NULL)
		return (1);
	load_images(data);
	ft_check_arg(argc, data);
	load_map(argv[1], data);
	mlx_loop_hook(data->mlx_ptr, &render, data);
	mlx_hook(data->win_ptr, KeyPress, KeyPressMask, &handle_keypress, data);
	mlx_hook(data->win_ptr, DestroyNotify, StructureNotifyMask, &on_destroy, data);
	mlx_loop(data->mlx_ptr);
	return (0);
}
