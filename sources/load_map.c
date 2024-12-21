/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaulnie <asaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:41:10 by asaulnie          #+#    #+#             */
/*   Updated: 2024/12/21 19:09:11 by asaulnie         ###   ########.fr       */
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
		data->map.grid[i] = line;
		line = get_next_line(fd);
		i++;
	}
	close(fd);
	if (line)
		free(line);
}

void	load_map_dimensions(int fd, t_data *data)
{
	size_t	line_count;
	char	*line;
	size_t	max_width;

	line_count = 0;
	line = get_next_line(fd);
	if (line == NULL)
		handle_error(ERR_EMPTY, data);
	else
		max_width = ft_strlen(line);
	while (line != NULL)
	{
		line_count++;
		data->map.height = line_count;
		data->map.width = max_width;
		if (max_width != ft_strlen(line))
		{
			free(line);
			handle_error(ERR_MAP_SIZE, data);
		}
		if (ft_strlen(line) > max_width)
			max_width = ft_strlen(line);
		free(line);
		line = get_next_line(fd);
	}
}

void	check_player(t_data *data)
{
	int	i;
	int	j;
	int	player;

	i = 0;
	player = 0;
	while (i < data->map.height)
	{
		j = 0;
		while (j < data->map.width)
		{
			if (data->map.grid[i][j] == 'P')
				player++;
			if (player == 2)
				handle_error(ERR_MULTI_P, data);
			j++;
		}
		i++;
	}
	if (player == 0)
		handle_error(ERR_NO_P, data);
}

void	check_exit(t_data *data)
{
	int	i;
	int	j;
	int	exit;

	i = 0;
	exit = 0;
	while (i < data->map.height)
	{
		j = 0;
		while (j < data->map.width)
		{
			if (data->map.grid[i][j] == 'E')
				exit++;
			if (exit == 2)
				handle_error(ERR_MULTI_E, data);
			j++;
		}
		i++;
	}
	if (exit == 0)
		handle_error(ERR_NO_E, data);
}

void	load_map(const char *filename, t_data *data)
{
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0 || data == NULL)
		handle_error(ERR_NO_MAP, data);
	load_map_dimensions(fd, data);
	close(fd);
	initialize_grid(data, filename);
	check_player(data);
	check_exit(data);
	flood_fill(data->map.grid, 1, 1, data);
}
