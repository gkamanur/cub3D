/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   borders.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 14:31:30 by gkamanur          #+#    #+#             */
/*   Updated: 2025/12/12 15:12:30 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parsing.h"

static int	has_visible_content(t_map_extents *ext)
{
	int	i;

	i = 0;
	while (i < ext->height)
	{
		if (ext->rows[i].start != -1)
			return (1);
		i++;
	}
	return (0);
}

static int	validate_all_rows(char **grid, t_map_extents *extents)
{
	int	y;

	y = 0;
	while (y < extents->height)
	{
		if (!validate_row_border(grid[y], extents->rows[y], y))
			return (0);
		y++;
	}
	return (1);
}

static int	validate_all_columns(char **grid, int width, int height)
{
	int	x;

	x = 0;
	while (x < width)
	{
		if (!validate_column(grid, x, height))
			return (0);
		x++;
	}
	return (1);
}

int	check_borders_strict(char **grid, int width, int height)
{
	t_map_extents	extents;

	if (!grid || width <= 0 || height <= 0)
	{
		printf("Error\nInvalid map data for border check\n");
		return (0);
	}
	extents = compute_row_extents(grid, height);
	if (!extents.rows)
		return (0);
	if (!has_visible_content(&extents))
	{
		printf("Error\nEmpty map\n");
		free_row_extents(&extents);
		return (0);
	}
	if (!validate_all_rows(grid, &extents) || !validate_all_columns(grid, width,
			height))
	{
		free_row_extents(&extents);
		return (0);
	}
	free_row_extents(&extents);
	return (1);
}
