/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_enclosure.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 11:55:00 by gkamanur          #+#    #+#             */
/*   Updated: 2025/12/19 14:49:15 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parsing.h"

static int	is_walkable(char c)
{
	return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static int	check_tile_neighbors(t_map *map, int x, int y)
{
	if (x < 0 || y < 0 || x >= map->width || y >= map->height)
		return (0);
	if (map->grid[y][x] == ' ')
	{
		printf("Error :Map not enclosed: \
			walkable tile at edge or next to space\n");
		printf("  at position (%d, %d)\n", y, x);
		return (0);
	}
	return (1);
}

static int	check_position_enclosed(t_map *map, int x, int y)
{
	if (!check_tile_neighbors(map, x - 1, y))
		return (0);
	if (!check_tile_neighbors(map, x + 1, y))
		return (0);
	if (!check_tile_neighbors(map, x, y - 1))
		return (0);
	if (!check_tile_neighbors(map, x, y + 1))
		return (0);
	return (1);
}

int	check_map_enclosure(char **grid, int width, int height)
{
	int		x;
	int		y;
	t_map	map;

	map.grid = grid;
	map.width = width;
	map.height = height;
	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			if (is_walkable(grid[y][x]))
			{
				if (!check_position_enclosed(&map, x, y))
					return (0);
			}
			x++;
		}
		y++;
	}
	return (1);
}
