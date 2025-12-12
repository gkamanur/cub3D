/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   column.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 14:57:25 by gkamanur          #+#    #+#             */
/*   Updated: 2025/12/12 15:12:36 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parsing.h"

int	get_column_extent(char **grid, int x, int height, t_extent *col)
{
	int	y;

	col->start = -1;
	col->end = -1;
	for (y = 0; y < height; y++)
	{
		if (grid[y][x] != ' ')
		{
			if (col->start == -1)
				col->start = y;
			col->end = y;
		}
	}
	return (col->start != -1);
}

int	check_column_border(char **grid, int x, t_extent col)
{
	if (grid[col.start][x] != '1')
	{
		printf("Error\nTop border invalid at (%d,%d): expected '1',\
			found '%c'\n", col.start, x, grid[col.start][x]);
		return (0);
	}
	if (grid[col.end][x] != '1')
	{
		printf("Error\nBottom border invalid at (%d,%d): expected '1',\
			found '%c'\n", col.end, x, grid[col.end][x]);
		return (0);
	}
	return (1);
}

int	validate_column(char **grid, int x, int height)
{
	t_extent col;

	if (!get_column_extent(grid, x, height, &col))
		return (1);
	return (check_column_border(grid, x, col));
}
