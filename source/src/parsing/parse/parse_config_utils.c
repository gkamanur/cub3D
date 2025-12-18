/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 15:14:47 by gkamanur          #+#    #+#             */
/*   Updated: 2025/12/18 13:25:39 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parsing.h"

int	config_complete(t_data *data)
{
	return (data->textures.north != NULL && data->textures.south != NULL
		&& data->textures.west != NULL && data->textures.east != NULL
		&& data->floor.r != -1 && data->ceiling.r != -1);
}

int handle_parse_result(int presult, char *trimmed, char *line)
{
    if (presult == 1)
    {
        free(trimmed);
        free(line);
        return 1;
    }

    if (presult == 0)
    {
        printf("Error\nInvalid or duplicate config line\n");
        free(trimmed);
        free(line);
        return 0;
    }
    free(trimmed);
    free(line);
    return 0;
}

void	handle_map_start(char *line, t_data *data)
{
	data->map.first_line = line;
}

int	parse_config_tokens(char *trimmed, t_data *data)
{
	if (ft_strncmp(trimmed, "NO ", 3) == 0 || ft_strncmp(trimmed, "SO ", 3) == 0
		|| ft_strncmp(trimmed, "WE ", 3) == 0 || ft_strncmp(trimmed, "EA ",
			3) == 0)
	{
		if (parse_texture(trimmed, &data->textures))
			return (1);
		return (0);
	}
	if (ft_strncmp(trimmed, "FT ", 3) == 0 || ft_strncmp(trimmed, "CT ",
			3) == 0)
	{
		if (parse_cf_texture(trimmed, &data->textures))
			return (1);
		return (0);
	}
	if (ft_strncmp(trimmed, "F ", 2) == 0 || ft_strncmp(trimmed, "C ", 2) == 0)
	{
		if (parse_color(trimmed, &data->floor, &data->ceiling))
			return (1);
		return (0);
	}
	return (-1);
}
