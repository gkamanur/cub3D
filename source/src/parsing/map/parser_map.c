/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 18:17:31 by gkamanur          #+#    #+#             */
/*   Updated: 2025/12/08 14:56:42 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parsing.h"

int pad_and_copy_lines(t_data * data, char **temp_lines, int count)
{
	int i;
	i = 0;
	while (i < count)
	{
		data->map.grid[i] = pad_line(temp_lines[i], data->map.width);
		free(temp_lines[i]);
		if (!data->map.grid[i])
		{
			while (i-- > 0)
				free(data->map.grid[i]);
			free(data->map.grid);
			return (0);
		}
		i++;
	}
	data->map.grid[count] = NULL;
	return (1);
}

int read_and_process_map(int fd, t_data *data, char ***out_lines,
	int *out_count)
{
	char **temp_lines;
	int count;
	temp_lines = allocate_temp_lines(1024);
	if (!temp_lines)
		return (0);
	count = 0;
	if (!process_first_line(data, temp_lines, &count))
	{
		free(temp_lines);
		return (0);
	}
	if (!read_map_lines(fd, temp_lines, &count))
	{
		free_temp_lines(temp_lines, count);
		return (0);
	}
	if (count == 0)
	{
		free(temp_lines);
		return (0);
	}
	*out_lines = temp_lines;
	*out_count = count;
	return (1);
}

int allocate_grid(t_data * data, char **temp_lines, int count)
{
	data->map.height = count;
	data->map.width = get_max_width(temp_lines, count);
	data->map.grid = malloc(sizeof(char *) * (count + 1));
	if (!data->map.grid)
		return (0);
	return (1);
}

int parse_map(int fd, t_data *data)
{
	char **temp_lines;
	int count;
	if (!read_and_process_map(fd, data, &temp_lines, &count))
		return (0);
	if (!allocate_grid(data, temp_lines, count))
	{
		free_temp_lines(temp_lines, count);
		return (0);
	}
	if (!pad_and_copy_lines(data, temp_lines, count))
	{
		free_temp_lines(temp_lines, count);
		return (0);
	}
	free(temp_lines);
	return (1);
}
