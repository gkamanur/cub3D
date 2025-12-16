/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 11:30:11 by gkamanur          #+#    #+#             */
/*   Updated: 2025/12/16 15:18:42 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parsing.h"

static int	validate_player(t_map *map, t_player *player)
{
	char	player_dir;
	int		player_count;

	player_count = find_player(map, player, &player_dir);
	if (!validate_player_count(player_count))
		return (0);
	init_player_direction(player, player_dir);
	return (1);
}

static int	validate_map_extents(t_map *map)
{
	t_map_extents	extents;

	extents = compute_row_extents(map->grid, map->height);
	if (!extents.rows)
	{
		printf("Error\nFailed to compute map extents\n");
		return (0);
	}
	if (!check_no_empty_rows(&extents) || !check_no_empty_columns(map->grid,
			&extents, map->width))
	{
		free_row_extents(&extents);
		printf("Error\nMap has empty rows or columns\n");
		return (0);
	}
	free_row_extents(&extents);
	return (1);
}

static int	validate_map_borders(t_map *map)
{
	if (!check_borders_strict(map->grid, map->width, map->height))
	{
		printf("Error\nMap not surrounded by walls\n");
		return (0);
	}
	return (1);
}

int	validate_map(t_map *map, t_player *player)
{
	if (!check_map_empty(map))
		return (0);
	if (!validate_player(map, player))
		return (0);
	if (!validate_map_extents(map))
		return (0);
	if (!validate_map_borders(map))
		return (0);
	return (1);
}
