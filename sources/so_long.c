/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaulnie <asaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 19:22:39 by asaulnie          #+#    #+#             */
/*   Updated: 2024/12/19 13:05:00 by asaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_map(t_data *data)
{
	int	i;

	if (!data->map.grid)
		return ;
	i = 0;
	while (i < data->map.height)
	{
		if (data->map.grid[i])
			free(data->map.grid[i]);
		i++;
	}
	free(data->map.grid);
	data->map.grid = NULL;
}

int	on_destroy(t_data *data, int exit_status)
{
	int	i;

	i = 0;
	while (i < 5)
	{
		mlx_destroy_image(data->mlx_ptr, data->textures[i]);
		i++;
	}
	free_map(data);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	data->mlx_ptr = NULL;
	exit(exit_status);
}

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

void	handle_error(int code, t_data *data)
{
	if (code == ERR_ARG)
		ft_printf("Error: Not enough arguments.\n");
	else if (code == ERR_EMPTY)
		ft_printf("Error: Map empty.\n");
	else if (code == ERR_MAP_SIZE)
		ft_printf("Error: Inconsistent row size.\n");
	else if (code == ERR_NO_MAP)
		ft_printf("Error: No map found.\n");
	else if (code == ERR_INV_CHAR)
		ft_printf("Error: Invalid character.\n");
	else if (code == ERR_NO_P)
		ft_printf("Error: Missing player.\n");
	else if (code == ERR_NO_E)
		ft_printf("Error: Missing exit.\n");
	else if (code == ERR_NOT_POSS)
		ft_printf("Error: No reachable exit.\n");
	else if (code == ERR_MULTI_P)
		ft_printf("Error: More than one player.\n");
	else if (code == ERR_MULTI_E)
		ft_printf("Error: More than one exit.\n");
	else
		ft_printf("Error: Unknown error.\n");
	on_destroy(data, 1);
}

void	data_setter(t_data *data)
{
	int	i;

	i = 0;
	data->mlx_ptr = NULL;
	data->win_ptr = NULL;
	while (i < 5)
	{
		data->textures[i] = NULL;
		data->textures_path[i] = NULL;
		i++;
	}
	data->map.width = 0;
	data->map.height = 0;
	data->map.grid = NULL;
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

int	main(int argc, char **argv)
{
	t_data	data;

	data_setter(&data);
	data.mlx_ptr = mlx_init();
	if (data.mlx_ptr == NULL)
		return (1);
	data.win_ptr = mlx_new_window(data.mlx_ptr, W, H, "so_long");
	if (data.win_ptr == NULL)
		return (1);
	load_images(&data);
	check_arg(argc, &data);
	load_map(argv[1], &data);
	find_player_start(&data);
	render(&data);
	// mlx_loop_hook(data.mlx_ptr, &render, &data);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);
	mlx_hook(data.win_ptr, DestroyNotify, StructureNotifyMask, &on_destroy, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
