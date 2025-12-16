/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_free_grid.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 14:55:26 by gkamanur          #+#    #+#             */
/*   Updated: 2025/12/16 15:10:18 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parsing.h"

char	**allocate_temp_lines(int size)
{
	char	**temp;

	temp = malloc(sizeof(char *) * size);
	return (temp);
}

void	free_temp_lines(char **lines, int count)
{
	while (count-- > 0)
		free(lines[count]);
	free(lines);
}

void	free_text_color(t_data *data)
{
	free(data->textures.north);
	free(data->textures.south);
	free(data->textures.west);
	free(data->textures.east);
	free(data->textures.floor_tex);
	free(data->textures.ceiling_tex);
}
