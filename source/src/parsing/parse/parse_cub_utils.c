/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cub_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 11:25:36 by gkamanur          #+#    #+#             */
/*   Updated: 2025/12/18 10:49:12 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parsing.h"

int	check_extension(const char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (len < 4 || strcmp(filename + len - 4, ".cub") != 0)
	{
		printf("Error\nFile must have .cub extension\n");
		return (0);
	}
	return (1);
}

int	open_cub_file(const char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		printf("Error\nCannot open file: %s\n", filename);
		return (-1);
	}
	return (fd);
}

int	parse_and_validate_config(int fd, t_data *data)
{
	if (!parse_config(fd, data, NULL))
		return (0);
	debug_print_textures(&data->textures);
	debug_print_colors(&data->floor, &data->ceiling);
	if (!parse_and_validate_textures(data) || !validate_colors(&data->floor,
			&data->ceiling))
	{
		free_data(data);
		return (0);
	}
	return (1);
}

int	parse_and_validate_map(int fd, t_data *data)
{
	if (!parse_map(fd, data))
	{
		free_map(data);
		printf("Error\nInvalid map\n");
		return (0);
	}
	if (!validate_map(&data->map, &data->player))
	{
		free_map(data);
		return (0);
	}
	return (1);
}
