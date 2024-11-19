/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaulnie <asaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 19:22:39 by asaulnie          #+#    #+#             */
/*   Updated: 2024/11/19 19:34:30 by asaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_map(t_data *data)
{
	int		i;

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
	int		i;

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
		ft_printf("Error: Missing Player.\n");
	else if (code == ERR_NO_P)
		ft_printf("Error: Missing wall.\n");
	else if (code == ERR_NOT_POSS)
		ft_printf("Error: No reachable exit.\n");
	else
		ft_printf("Error: Unknown error occurred.\n");
	on_destroy(data, 1);
}

void data_setter(t_data *data)
{
	int i;

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
	render(&data);
	// mlx_loop_hook(data.mlx_ptr, &render, &data);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);
	mlx_hook(data.win_ptr, DestroyNotify, StructureNotifyMask, &on_destroy, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
