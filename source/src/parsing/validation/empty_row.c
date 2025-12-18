/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   empty_row.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 11:35:40 by gkamanur          #+#    #+#             */
/*   Updated: 2025/12/17 09:49:05 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parsing.h"

static int	find_row_bounds(t_map_extents *ext, int *top, int *bottom)
{
	int	y;

	y = 0;
	*top = -1;
	*bottom = -1;
	while (y < ext->height)
	{
		if (ext->rows[y].start != -1)
		{
			if (*top == -1)
				*top = y;
			*bottom = y;
		}
		y++;
	}
	return (*top != -1);
}

int	check_no_empty_rows(t_map_extents *ext)
{
	int	y;
	int	top;
	int	bottom;

	if (!find_row_bounds(ext, &top, &bottom))
		return (0);
	y = top;
	while (y <= bottom)
	{
		if (ext->rows[y].start == -1)
		{
			printf("Error\nEmpty row inside map at y=%d (possible hole)\n", y);
			return (0);
		}
		y++;
	}
	return (1);
}
