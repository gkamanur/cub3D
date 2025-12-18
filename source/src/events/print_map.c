/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 13:33:12 by gkamanur          #+#    #+#             */
/*   Updated: 2025/12/18 13:41:44 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../includes/rendering.h"

void	print_column_numbers(int width)
{
	int	x;
	int	dozens;

	printf("     ");
	x = 0;
	while (x < width)
	{
		dozens = x / 10;
		if (dozens > 0)
			printf("%d", dozens);
		else
			printf(" ");
		x++;
	}
	printf("\n     ");
	x = 0;
	while (x < width)
	{
		printf("%d", x % 10);
		x++;
	}
	printf("\n");
}

void	print_horizontal_border(int width)
{
	int	x;

	x = 0;
	printf("    +");
	while (x < width)
	{
		printf("-");
		x++;
	}
	printf("+\n");
}

void	print_map_row(int y, t_map *map)
{
	int	x;

	x = 0;
	printf("%3d |", y);
	while (x < map->width)
	{
		printf("%c", map->grid[y][x]);
		x++;
	}
	printf("|\n");
}

void	debug_print_map_detailed(t_map *map)
{
	int	y;
	
	y = 0;
	printf("\nMap (Detailed with coordinates):\n");
	printf("  Size: %d x %d\n\n", map->width, map->height);
	print_column_numbers(map->width);
	print_horizontal_border(map->width);
	while (y < map->height)
	{
		print_map_row(y, map);
		y++;
	}
	print_horizontal_border(map->width);
}
