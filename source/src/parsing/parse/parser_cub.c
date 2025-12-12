/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cub.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 16:23:22 by gkamanur          #+#    #+#             */
/*   Updated: 2025/12/12 15:14:01 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parsing.h"

static int	check_extension(const char *filename)
{
	int len = ft_strlen(filename);

	if (len < 4 || strcmp(filename + len - 4, ".cub") != 0)
	{
		printf("Error\nFile must have .cub extension\n");
		return (0);
	}
	return (1);
}

static int	open_cub_file(const char *filename)
{
	int fd = open(filename, O_RDONLY);

	if (fd < 0)
	{
		printf("Error\nCannot open file: %s\n", filename);
		return (-1);
	}
	return fd;
}

static int	parse_and_validate_config(int fd, t_data *data)
{
	if (!parse_config(fd, data, NULL))
		return (0);
	if (!validate_textures(&data->textures) || 
		!validate_colors(&data->floor, &data->ceiling))
		return (0);
	return (1);
}

static int	parse_and_validate_map(int fd, t_data *data)
{
	if (!parse_map(fd, data))
	{
		printf("Error\nInvalid map\n");
		return (0);
	}
	if (!validate_map(&data->map, &data->player))
		return (0);
	return (1);
}

int	parse_cub_file(char *filename, t_data *data)
{
	int fd;

	if (!check_extension(filename))
		return (0);
	fd = open_cub_file(filename);
	if (fd < 0)
		return (0);
	init_data(data);
	if (!parse_and_validate_config(fd, data))
	{
		close(fd);
		return (0);
	}
	if (!parse_and_validate_map(fd, data))
	{
		close(fd);
		return (0);
	}
	close(fd);
	printf("✓ Map parsed successfully\n");
	printf("  Map size: %dx%d\n", data->map.width, data->map.height);
	printf("  Player at: (%.1f, %.1f)\n", data->player.x, data->player.y);
	return (1);
}
