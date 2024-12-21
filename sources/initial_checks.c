/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initial_checks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaulnie <asaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 18:19:34 by asaulnie          #+#    #+#             */
/*   Updated: 2024/12/21 20:27:59 by asaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check_arg(int argc, char **argv, t_data *data)
{
	const char	*filename;
	const char	*last_dot;

	if (argc != 2)
		handle_error2(ERR_ARG, data);
	filename = argv[1];
	last_dot = strrchr(filename, '.');
	if (!last_dot || strcmp(last_dot, ".ber") != 0
		|| strchr(filename, '.') != last_dot)
		handle_error2(ERR_EXT, data);
}

void	check_map_size(t_data *data, int map_width, int map_height)
{
	int	screen_width;
	int	screen_height;

	mlx_get_screen_size(data->mlx_ptr, &screen_width, &screen_height);
	if (map_width > screen_width || map_height > screen_height)
		handle_error2(ERR_MAP_BIG, data);
}

void	handle_error2(int code, t_data *data)
{
	if (code == ERR_ARG)
		ft_printf("Error: Not enough arguments.\n");
	else if (code == ERR_EXT)
		ft_printf("Error: Map extension invalid.\n");
	else if (code == ERR_MAP_BIG)
		ft_printf("Error: Map exceeds window size.\n");
	on_destroy(data, 1);
}

int	total_collectibles(char **map, int width, int height)
{
	int	count;
	int	y;
	int	x;

	count = 0;
	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			if (map[y][x] == 'C')
				count++;
			x++;
		}
		y++;
	}
	return (count);
}
