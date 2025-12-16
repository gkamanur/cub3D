/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_free_grid.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 14:55:26 by gkamanur          #+#    #+#             */
/*   Updated: 2025/12/15 12:01:38 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parsing.h"

char	**allocate_temp_lines(int size)
{
	char	**temp;

	temp = malloc(sizeof(char *) * size);
	return (temp);
}

void	free_temp_lines(char **lines, int count)
{
	while (count-- > 0)
		free(lines[count]);
	free(lines);
}

void free_text_color( t_data *data)
{
	free(data->textures.north);
    free(data->textures.south);
    free(data->textures.west);
    free(data->textures.east);
    free(data->textures.floor_tex);
    free(data->textures.ceiling_tex);
}

void free_data(t_data *data)
{
	free_text_color(data);
    if (data->map.grid)
    {
        for (int i = 0; i < data->map.height; i++)
            free(data->map.grid[i]);
        free(data->map.grid);
        data->map.grid = NULL;
    }
    free(data->map.first_line);
	if (data->mlx_ptr)
    {
        if (data->win_ptr)
        {
            mlx_destroy_window(data->mlx_ptr, data->win_ptr);
            data->win_ptr = NULL;
        }
        mlx_destroy_display(data->mlx_ptr);
        free(data->mlx_ptr);
        data->mlx_ptr = NULL;
    }
}
