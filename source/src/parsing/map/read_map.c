/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 14:57:52 by gkamanur          #+#    #+#             */
/*   Updated: 2025/12/19 14:58:18 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parsing.h"

static int	handle_non_map_content(char *trimmed)
{
	if (trimmed && ft_strlen(trimmed) > 0)
	{
		free(trimmed);
		return (0);
	}
	if (trimmed)
		free(trimmed);
	return (1);
}

static int	check_empty_line_in_map(int fd, char *line)
{
	char	*next_line;

	next_line = gnl(fd);
	if (next_line && is_map_line(next_line))
	{
		printf("Error\nEmpty line inside map\n");
		free(next_line);
		free(line);
		return (0);
	}
	if (next_line)
		free(next_line);
	return (1);
}

static int	process_non_map_line(int fd, char *line, int map_started)
{
	char	*trimmed;

	trimmed = my_strtrim(line);
	if (!handle_non_map_content(trimmed))
	{
		free(line);
		return (0);
	}
	if (map_started)
	{
		if (!check_empty_line_in_map(fd, line))
			return (0);
		free(line);
		return (2);
	}
	free(line);
	return (1);
}

int	read_map_lines_with_state(int fd, char **temp_lines, int *count,
		int map_started)
{
	char	*line;
	int		result;

	line = gnl(fd);
	while (line != NULL)
	{
		if (!is_map_line(line))
		{
			result = process_non_map_line(fd, line, map_started);
			if (result == 0)
				return (0);
			if (result == 2)
				break ;
			line = gnl(fd);
			continue ;
		}
		map_started = 1;
		temp_lines[(*count)++] = line;
		if (*count >= MAX_LINES)
			break ;
		line = gnl(fd);
	}
	return (1);
}
