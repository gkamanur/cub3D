/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_enclosure.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 11:55:00 by gkamanur          #+#    #+#             */
/*   Updated: 2025/12/18 13:25:09 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parsing.h"

static int	is_walkable(char c)
{
	return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static int	check_tile_neighbors(char **grid, int x, int y, int width,
		int height)
{
	if (x < 0 || y < 0 || x >= width || y >= height)
		return (0);
	if (grid[y][x] == ' ')
	{
		printf("Error\nMap not enclosed: walkable tile at edge or next to space\n");
		printf("  at position (%d, %d)\n", y, x);
		return (0);
	}
	return (1);
}

static int	check_position_enclosed(char **grid, int x, int y, int width,
		int height)
{
	if (!check_tile_neighbors(grid, x - 1, y, width, height))
		return (0);
	if (!check_tile_neighbors(grid, x + 1, y, width, height))
		return (0);
	if (!check_tile_neighbors(grid, x, y - 1, width, height))
		return (0);
	if (!check_tile_neighbors(grid, x, y + 1, width, height))
		return (0);
	return (1);
}

int	check_map_enclosure(char **grid, int width, int height)
{
	int	x;
	int	y;

	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			if (is_walkable(grid[y][x]))
			{
				if (!check_position_enclosed(grid, x, y, width, height))
					return (0);
			}
			x++;
		}
		y++;
	}
	return (1);
}
