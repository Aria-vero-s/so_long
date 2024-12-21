/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaulnie <asaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 18:19:34 by asaulnie          #+#    #+#             */
/*   Updated: 2024/12/21 18:25:11 by asaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check_arg(int argc, char **argv, t_data *data)
{
	int	len;
	int	i;

	i = 0;
	if (argc != 2)
	{
		handle_error(ERR_ARG, data);
		return ;
	}
	len = ft_strlen(argv[1]);
	if (len < 4 || ft_strncmp(argv[1] + len - 4, ".ber", len) != 0)
	{
		handle_error(ERR_EXT, data);
		return ;
	}
	while (i < len - 4)
	{
		if (argv[1][i] == '.')
		{
			handle_error(ERR_EXT, data);
			return ;
		}
		i++;
	}
}

void	check_map_size(t_data *data, int map_width, int map_height)
{
	int	screen_width;
	int	screen_height;

	mlx_get_screen_size(data->mlx_ptr, &screen_width, &screen_height);
	if (map_width > screen_width || map_height > screen_height)
		handle_error(ERR_MAP_BIG, data);
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
