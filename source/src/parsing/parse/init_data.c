/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 16:18:52 by gkamanur          #+#    #+#             */
/*   Updated: 2025/12/04 18:27:57 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

static void	init_player(t_player *player)
{
	player->x = 0;
	player->y = 0;
	player->dir_x = 0;
	player->dir_y = 0;
	player->plane_x = 0;
	player->plane_y = 0;
}

static void	init_map(t_map *map)
{
	map->grid = NULL;
	map->width = 0;
	map->height = 0;
	map->first_line = NULL;
}

static void	init_colors(t_color *floor, t_color *ceiling)
{
	floor->r = -1;
	floor->g = -1;
	floor->b = -1;
	ceiling->r = -1;
	ceiling->g = -1;
	ceiling->b = -1;
}

static void	init_textures(t_textures *tex)
{
	tex->north = NULL;
	tex->south = NULL;
	tex->west = NULL;
	tex->east = NULL;
	tex->floor_tex = NULL;
	tex->ceiling_tex = NULL;
}

void	init_data(t_data *data)
{
	data->mlx_ptr = NULL;
	data->win_ptr = NULL;
	init_textures(&data->textures);
	init_colors(&data->floor, &data->ceiling);
	init_map(&data->map);
	init_player(&data->player);
	data->use_floor_texture = 0;
	data->use_ceiling_texture = 0;
	data->texture_mode = 1;
	data->torch_mode = 0;
}
