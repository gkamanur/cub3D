/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rows.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 14:59:48 by gkamanur          #+#    #+#             */
/*   Updated: 2025/12/12 15:12:56 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parsing.h"

void	free_row_extents(t_map_extents *ext)
{
	if (ext && ext->rows)
		free(ext->rows);
	ext->rows = NULL;
	ext->height = 0;
}

t_extent	get_row_extent(char *row)
{
	t_extent	ext;
	int			i;

	ext.start = -1;
	ext.end = -1;
	i = 0;
	while (row[i])
	{
		if (row[i] != ' ')
		{
			if (ext.start == -1)
				ext.start = i;
			ext.end = i;
		}
		i++;
	}
	return (ext);
}
int	validate_row_border(char *row, t_extent ext, int y)
{
	if (ext.start == -1)
		return (1);
	if (row[ext.start] != '1')
	{
		printf("Error\nLeft border invalid at (%d,%d): expected '1',\
			found '%c'\n",
				y,
				ext.start,
				row[ext.start]);
		return (0);
	}
	if (row[ext.end] != '1')
	{
		printf("Error\nRight border invalid at (%d,%d): expected '1',\
			found '%c'\n",
				y,
				ext.end,
				row[ext.end]);
		return (0);
	}
	return (1);
}

t_map_extents	compute_row_extents(char **grid, int height)
{
	t_map_extents	extents;
	int				y;

	extents.height = height;
	extents.rows = malloc(sizeof(t_extent) * height);
	if (!extents.rows)
	{
		extents.height = 0;
		return (extents);
	}
	y = 0;
	while (y < height)
	{
		extents.rows[y] = get_row_extent(grid[y]);
		y++;
	}
	return (extents);
}
