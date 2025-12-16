/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm_file_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 15:32:05 by gkamanur          #+#    #+#             */
/*   Updated: 2025/12/16 10:45:40 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parsing.h"

static int	validate_texture_data(t_data *data)
{
	if (!data || !data->mlx_ptr)
	{
		fprintf(stderr, "Error: Invalid data structure\n");
		return (0);
	}
	return (1);
}

static int	validate_single_texture(void *mlx_ptr, char *path, const char *name)
{
	if (!validate_xpm_path(mlx_ptr, path))
	{
		fprintf(stderr, "Error: Invalid XPM file for %s texture: %s\n", name,
			path ? path : "(null)");
		return (0);
	}
	return (1);
}

int	parse_and_validate_textures(t_data *data)
{
	if (!validate_texture_data(data))
		return (0);
	printf("north :%s\n", data->textures.north);
	if (!validate_single_texture(data->mlx_ptr, data->textures.north, "North"))
		return (0);
	if (!validate_single_texture(data->mlx_ptr, data->textures.south, "South"))
		return (0);
	if (!validate_single_texture(data->mlx_ptr, data->textures.east, "East"))
		return (0);
	if (!validate_single_texture(data->mlx_ptr, data->textures.west, "West"))
		return (0);
	return (1);
}
