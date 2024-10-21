/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaulnie <asaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 19:22:39 by asaulnie          #+#    #+#             */
/*   Updated: 2024/10/21 19:27:48 by asaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdlib.h>

int	close_window(int keycode, void *param)
{
	(void)param;
	if (keycode == 65307)
		exit(0);
	return (0);
}

int	close_event(void *param)
{
	(void)param;
	exit(0);
	return (0);
}

int	main(void)
{
	void	*mlx_ptr;
	void	*win_ptr;

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 800, 600, "so_long");
	mlx_hook(win_ptr, 2, 1L << 0, close_window, NULL);
	mlx_hook(win_ptr, 17, 0L, close_event, NULL);
	mlx_loop(mlx_ptr);
	return (0);
}
