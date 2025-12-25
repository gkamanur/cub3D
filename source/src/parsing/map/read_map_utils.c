/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 14:51:09 by gkamanur          #+#    #+#             */
/*   Updated: 2025/12/19 15:00:35 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parsing.h"
#define MAX_LINES 1024

int	is_map_line(char *line)
{
	int	i;

	if (!line || strlen(line) == 0)
		return (0);
	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '1' && line[i] != '0' && line[i] != 'N'
			&& line[i] != 'S' && line[i] != 'E' && line[i] != 'W')
			return (0);
		i++;
	}
	return (1);
}

int	get_max_width(char **lines, int count)
{
	int	max;
	int	len;
	int	i;

	max = 0;
	i = 0;
	while (i < count)
	{
		len = strlen(lines[i]);
		if (len > max)
			max = len;
		i++;
	}
	return (max);
}

char	*pad_line(char *line, int width)
{
	char	*padded;
	int		len;
	int		i;

	len = strlen(line);
	padded = malloc(width + 1);
	if (!padded)
		return (NULL);
	i = 0;
	while (i < len)
	{
		padded[i] = line[i];
		i++;
	}
	while (i < width)
	{
		padded[i] = ' ';
		i++;
	}
	padded[width] = '\0';
	return (padded);
}

int	process_first_line(t_data *data, char **temp_lines, int *count)
{
	if (data->map.first_line)
	{
		if (is_map_line(data->map.first_line))
		{
			temp_lines[(*count)++] = data->map.first_line;
			data->map.first_line = NULL;
		}
		else
		{
			free(data->map.first_line);
			data->map.first_line = NULL;
			return (0);
		}
	}
	return (1);
}

int	is_all_spaces(const char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}
