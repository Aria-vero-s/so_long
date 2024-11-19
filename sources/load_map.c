/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaulnie <asaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:41:10 by asaulnie          #+#    #+#             */
/*   Updated: 2024/11/19 17:19:32 by asaulnie         ###   ########.fr       */
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

void	load_map_dimensions(int fd, t_data *data, size_t *max_width)
{
	size_t	line_count;
	char	*line;

	line_count = 0;
	line = get_next_line(fd);
	if (line == NULL)
		handle_error(ERR_EMPTY, data);
	else
		*max_width = ft_strlen(line);
	while (line != NULL)
	{
		line_count++;
		data->map.height = line_count;
		if (*max_width != ft_strlen(line))
		{
			free(line);
			handle_error(ERR_MAP_SIZE, data);
		}
		if (ft_strlen(line) > *max_width)
			*max_width = ft_strlen(line);
		free(line);
		line = get_next_line(fd);
	}
}

void	fill(char **tab, int width, int height, int x, int y, char c)
{
	if (x < 0 || y < 0 || x >= width || y >= height || tab[y][x] != c)
		return ;
	tab[y][x] = 'F';
	printf("tab[y][x]:%c\n", tab[y][x]);
	fill(tab, width, height, x, y + 1, c);
	fill(tab, width, height, x, y - 1, c);
	fill(tab, width, height, x + 1, y, c);
	fill(tab, width, height, x - 1, y, c);
}

void	flood_fill(char **tab, int width, int height, int x, int y)
{
	char	c;

	c = tab[y][x];
	printf("c:%c, width:%d, height:%d, x:%d, y:%d\n", c, width, height, x, y);
	fill(tab, width, height, x, y, c);
}

void	load_map(const char *filename, t_data *data)
{
	int		fd;
	int		i;
	//char	*line;
	size_t	max_width;
	// int		width;
	//int		x;
	//int		y;

	i = 0;
	fd = open(filename, O_RDONLY);
	// line = get_next_line(fd);
	// x = 0;
	// y = 0;
	// if (line != NULL)
	// 	width = ft_strlen(line);
	if (fd < 0 || data == NULL)
		handle_error(ERR_NO_MAP, data);
	load_map_dimensions(fd, data, &max_width);
	close(fd);
	data->map.width = max_width;
	initialize_grid(data, filename);
	// flood_fill(data->map.grid, width, data->map.height, x, y);
	while (i < data->map.height)
	{
		printf("%s", data->map.grid[i]);
		i++;
	}
}
