/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaulnie <asaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:41:10 by asaulnie          #+#    #+#             */
/*   Updated: 2024/12/21 20:02:22 by asaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	fill(char **tab, t_fill_params *params, int x, int y)
{
	int	w;
	int	h;

	w = params->data->map.width;
	h = params->data->map.height;
	if (x < 0 || y < 0 || x >= w
		|| y >= h || tab[y][x] == '1' || tab[y][x] == 'V')
		return ;
	if (tab[y][x] == 'P')
		*(params->player) = 1;
	else if (tab[y][x] == 'E')
		*(params->exit) = 1;
	else if (tab[y][x] == 'C')
		*(params->collected) += 1;
	tab[y][x] = 'V';
	fill(tab, params, x, y + 1);
	fill(tab, params, x, y - 1);
	fill(tab, params, x + 1, y);
	fill(tab, params, x - 1, y);
}

char	**copy_map(char **tab, int height)
{
	int		i;
	char	**copy;

	copy = malloc(height * sizeof(char *));
	i = 0;
	while (i < height)
	{
		copy[i] = strdup(tab[i]);
		i++;
	}
	return (copy);
}

void	free_map_copy(char **copy, int height)
{
	int	i;

	i = 0;
	while (i < height)
	{
		free(copy[i]);
		i++;
	}
	free(copy);
}

void	flood_fill(char **tab, int x, int y, t_data *data)
{
	int				player;
	int				exit;
	int				collected;
	char			**copy;
	t_fill_params	params;

	player = 0;
	exit = 0;
	collected = 0;
	copy = copy_map(tab, data->map.height);
	params.collected = &collected;
	params.player = &player;
	params.exit = &exit;
	params.data = data;
	fill(copy, &params, x, y);
	free_map_copy(copy, data->map.height);
	if (*params.collected != total_collectibles
		(tab, data->map.width, data->map.height))
		handle_error(ERR_C_UNREACH, data);
	if (!player || !exit)
		handle_error(ERR_NOT_POSS, data);
}
