/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaulnie <asaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 19:22:39 by asaulnie          #+#    #+#             */
/*   Updated: 2024/12/21 18:23:06 by asaulnie         ###   ########.fr       */
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
		if (data->textures[i] != NULL)
			mlx_destroy_image(data->mlx_ptr, data->textures[i]);
		i++;
	}
	free_map(data);
	if (data->win_ptr != NULL)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	data->mlx_ptr = NULL;
	exit(exit_status);
}

void	handle_error(int code, t_data *data)
{
	if (code == ERR_EMPTY)
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
	else if (code == ERR_NO_IMG)
		ft_printf("Error: Images not accessible.\n");
	on_destroy(data, 1);
}

void	data_setter(t_data *data)
{
	int	i;

	i = 0;
	data->mlx_ptr = mlx_init();
	if (data->mlx_ptr == NULL)
	{
		ft_printf("Error: mlx failed.\n");
		exit(1);
	}
	data->win_ptr = NULL;
	while (i < 5)
	{
		data->textures[i] = NULL;
		data->path[i] = NULL;
		i++;
	}
	data->map.width = 0;
	data->map.height = 0;
	data->map.grid = NULL;
	data->collected_count = 0;
	data->total_chests = 0;
	data->player_x = 0;
	data->player_y = 0;
	data->steps = 0;
}

int	main(int argc, char **argv)
{
	t_data	data;
	int		w;
	int		h;

	data_setter(&data);
	if (data.mlx_ptr == NULL)
		return (1);
	load_images(&data);
	check_arg(argc, argv, &data);
	load_map(argv[1], &data);
	w = (data.map.width - 1) * TILE_SIZE;
	h = data.map.height * TILE_SIZE;
	check_map_size(&data, w, h);
	data.win_ptr = mlx_new_window(data.mlx_ptr, w, h, "so_long");
	if (data.win_ptr == NULL)
		return (1);
	count_collectibles(&data);
	find_player_start(&data);
	render(&data);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);
	mlx_hook
		(data.win_ptr, DestroyNotify, StructureNotifyMask, &on_destroy, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
