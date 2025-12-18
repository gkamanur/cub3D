/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 15:10:13 by gkamanur          #+#    #+#             */
/*   Updated: 2025/12/17 12:54:10 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parsing.h"

void	free_map(t_data *data)
{
	int	i;

	if (data->map.grid)
	{
		i = 0;
		while (i < data->map.height)
		{
			free(data->map.grid[i]);
			i++;
		}
		free(data->map.grid);
		data->map.grid = NULL;
	}

	if (data->map.first_line)
	{
		free(data->map.first_line);
		data->map.first_line = NULL;
	}

	data->map.width = 0;
	data->map.height = 0;
}

static void	free_mlx(t_data *data)
{
	if (!data->mlx_ptr)
		return ;
	if (data->win_ptr)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		data->win_ptr = NULL;
	}
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	data->mlx_ptr = NULL;
}

void	free_text_color(t_data *data)
{
	if (!data)
		return;
		
	if (data->textures.north)
		free(data->textures.north);
	if (data->textures.south)
		free(data->textures.south);
	if (data->textures.west)
		free(data->textures.west);
	if (data->textures.east)
		free(data->textures.east);
	if (data->textures.floor_tex)
		free(data->textures.floor_tex);
	if (data->textures.ceiling_tex)
		free(data->textures.ceiling_tex);
	data->textures.north = NULL;
	data->textures.south = NULL;
	data->textures.west = NULL;
	data->textures.east = NULL;
	data->textures.floor_tex = NULL;
	data->textures.ceiling_tex = NULL;
}
void	free_data(t_data *data)
{
	if (!data)
		return ;
	free_text_color(data);
	free_map(data);
	free_mlx(data);
}
