/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   empty_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 19:17:02 by gkamanur          #+#    #+#             */
/*   Updated: 2025/12/12 19:22:10 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parsing.h"

static t_extent get_column_ext_empty(char **grid, int height, int x)
{
	t_extent ext;
	int y;

	ext.start = -1;
	ext.end = -1;
	y = 0;
	while (y < height)
	{
		if (grid[y][x] != ' ')
		{
			if (ext.start == -1)
				ext.start = y;
			ext.end = y;
		}
		y++;
	}
	return ext;
}

int check_no_empty_columns(char **grid, t_map_extents *ext, int width)
{
	int x;
	int min_left = -1;
	int max_right = -1;

	for (x = 0; x < ext->height; x++)
	{
		if (ext->rows[x].start != -1)
		{
			if (min_left == -1 || ext->rows[x].start < min_left)
				min_left = ext->rows[x].start;
			if (ext->rows[x].end > max_right)
				max_right = ext->rows[x].end;
		}
	}
	if (min_left == -1)
		return 0;
	for (x = min_left; x <= max_right && x < width; x++)
	{
		t_extent col = get_column_ext_empty(grid, ext->height, x);
		if (col.start == -1)
		{
			printf("Error\nEmpty column inside map at x=%d (possible hole)\n", x);
			return 0;
		}
	}
	return 1;
}

int check_no_empty_rows(t_map_extents *ext)
{
	int top = -1;
	int bottom = -1;
	int y;
	for (y = 0; y < ext->height; y++)
	{
		if (ext->rows[y].start != -1)
		{
			if (top == -1)
				top = y;
			bottom = y;
		}
	}
	if (top == -1)
		return 0;
	for (y = top; y <= bottom; y++)
	{
		if (ext->rows[y].start == -1)
		{
			printf("Error\nEmpty row inside map at y=%d (possible hole)\n", y);
			return 0;
		}
	}
	return 1;
}
