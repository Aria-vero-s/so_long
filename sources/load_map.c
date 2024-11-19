/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaulnie <asaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:41:10 by asaulnie          #+#    #+#             */
/*   Updated: 2024/11/19 21:40:44 by asaulnie         ###   ########.fr       */
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

void	fill(char **tab, int width, int height, int x, int y, int *player, int *exit)
{
	if (x < 0 || y < 0 || x >= width || y >= height || tab[y][x] == '1' || tab[y][x] == 'V')
		return;
	if (tab[y][x] == 'P')
		*player = 1;
	else if (tab[y][x] == 'E')
		*exit = 1;
	tab[y][x] = 'V';
	fill(tab, width, height, x, y + 1, player, exit);
	fill(tab, width, height, x, y - 1, player, exit);
	fill(tab, width, height, x + 1, y, player, exit);
	fill(tab, width, height, x - 1, y, player, exit);
}

void	flood_fill(char **tab, int width, int height, int x, int y, t_data *data)
{
	int player;
	int exit;

	player = 0;
	exit = 0;
	fill(tab, width, height, x, y, &player, &exit);
	if (!player || !exit)
		handle_error(ERR_NOT_POSS, data);
}

void	load_map(const char *filename, t_data *data)
{
	int		fd;
	int		i;

	fd = open(filename, O_RDONLY);
	i = 0;
	if (fd < 0 || data == NULL)
		handle_error(ERR_NO_MAP, data);
	load_map_dimensions(fd, data);
	close(fd);
	initialize_grid(data, filename);
	flood_fill(data->map.grid, data->map.width, data->map.height, 1, 1, data);
	while (i < data->map.height)
	{
		printf("%s", data->map.grid[i]);
		i++;
	}
}
