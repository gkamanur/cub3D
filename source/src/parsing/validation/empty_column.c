/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   empty_column.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 11:34:57 by gkamanur          #+#    #+#             */
/*   Updated: 2025/12/17 09:48:20 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parsing.h"

static t_extent	get_column_ext_empty(char **grid, int height, int x)
{
	t_extent	ext;
	int			y;

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
	return (ext);
}

static int	find_column_bounds(t_map_extents *ext, int *min_left,
		int *max_right)
{
	int	x;

	x = 0;
	*min_left = -1;
	*max_right = -1;
	while (x < ext->height)
	{
		if (ext->rows[x].start != -1)
		{
			if (*min_left == -1 || ext->rows[x].start < *min_left)
				*min_left = ext->rows[x].start;
			if (ext->rows[x].end > *max_right)
				*max_right = ext->rows[x].end;
		}
		x++;
	}
	return (*min_left != -1);
}

int	check_no_empty_columns(char **grid, t_map_extents *ext, int width)
{
	int			x;
	t_extent	col;
	int			min_left;
	int			max_right;

	if (!find_column_bounds(ext, &min_left, &max_right))
		return (0);
	x = min_left;
	while (x <= max_right && x < width)
	{
		col = get_column_ext_empty(grid, ext->height, x);
		if (col.start == -1)
		{
			printf("Error\nEmpty column inside map at x=%d (possible hole)\n",
				x);
			return (0);
		}
		x++;
	}
	return (1);
}
