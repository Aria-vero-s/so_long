/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaulnie <asaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:41:10 by asaulnie          #+#    #+#             */
/*   Updated: 2024/11/13 14:43:47 by asaulnie         ###   ########.fr       */
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
	if (line != NULL)
		*max_width = ft_strlen(line);
	else
		*max_width = 0;
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

void	load_map(const char *filename, t_data *data)
{
	size_t	max_width;
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0 || data == NULL)
		handle_error(ERR_NO_MAP, data);
	load_map_dimensions(fd, data, &max_width);
	close(fd);
	data->map.width = max_width;
	initialize_grid(data, filename);
}
