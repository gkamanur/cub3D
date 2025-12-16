/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pad_and_copy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 15:00:36 by gkamanur          #+#    #+#             */
/*   Updated: 2025/12/16 15:02:49 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parsing.h"

static char	*allocate_padded_line(const char *src, int width)
{
	int		len;
	char	*new_line;

	len = 0;
	while (src[len] && src[len] != '\n')
		len++;
	new_line = malloc(width + 1);
	if (!new_line)
		return (NULL);
	ft_memcpy(new_line, src, len);
	ft_memset(new_line + len, ' ', width - len);
	new_line[width] = '\0';
	return (new_line);
}

static void	free_lines(char **lines, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(lines[i]);
		i++;
	}
}

int	pad_and_copy_lines(t_data *data, char **temp_lines, int count)
{
	int		i;
	char	*new_line;

	i = 0;
	while (i < count)
	{
		new_line = allocate_padded_line(temp_lines[i], data->map.width);
		if (!new_line)
		{
			while (i > 0)
				free(data->map.grid[--i]);
			free_lines(temp_lines, count);
			return (0);
		}
		free(temp_lines[i]);
		data->map.grid[i] = new_line;
		i++;
	}
	data->map.grid[count] = NULL;
	return (1);
}
