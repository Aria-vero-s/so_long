/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaulnie <asaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 14:21:00 by asaulnie          #+#    #+#             */
/*   Updated: 2024/12/19 14:22:46 by asaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	render(t_data *data)
{
	if (data->map.grid)
		render_map(data, data->map.grid, data->map.width, data->map.height);
	else
		ft_printf("Map or grid is NULL!\n");
	return (0);
}

void	move_player(t_data *data, int new_x, int new_y)
{
	if (data->map.grid[new_y][new_x] == '0')
	{
		data->map.grid[data->player_y][data->player_x] = '0';
		data->map.grid[new_y][new_x] = 'P';
		data->player_x = new_x;
		data->player_y = new_y;
		render(data);
	}
}

int	handle_keypress(int key, t_data *data)
{
	if (key == XK_Escape)
		on_destroy(data, 0);
	else if (key == KEY_W || key == XK_Up)
		move_player(data, data->player_x, data->player_y - 1);
	else if (key == KEY_S || key == XK_Down)
		move_player(data, data->player_x, data->player_y + 1);
	else if (key == KEY_A || key == XK_Left)
		move_player(data, data->player_x - 1, data->player_y);
	else if (key == KEY_D || key == XK_Right)
		move_player(data, data->player_x + 1, data->player_y);
	return (0);
}

void	find_player_start(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	while (y < data->map.height)
	{
		x = 0;
		while (x < data->map.width)
		{
			if (data->map.grid[y][x] == 'P')
			{
				data->player_x = x;
				data->player_y = y;
				return ;
			}
			x++;
		}
		y++;
	}
}
