/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cub.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 16:23:22 by gkamanur          #+#    #+#             */
/*   Updated: 2025/12/16 15:12:32 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parsing.h"

static int	open_and_validate_file(const char *filename)
{
	int	fd;

	if (!check_extension(filename))
	{
		printf("Error\nInvalid file extension\n");
		return (-1);
	}
	fd = open_cub_file(filename);
	if (fd < 0)
	{
		printf("Error\nFailed to open file\n");
		return (-1);
	}
	return (fd);
}

static int	initialize_mlx(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
	{
		printf("Error\nFailed to initialize MiniLibX\n");
		return (0);
	}
	return (1);
}

static int	parse_config_and_map(int fd, t_data *data)
{
	if (!parse_and_validate_config(fd, data))
		return (0);
	if (!parse_and_validate_map(fd, data))
		return (0);
	return (1);
}

int	parse_cub_file(char *filename, t_data *data)
{
	int	fd;

	init_data(data);
	fd = open_and_validate_file(filename);
	if (fd < 0)
		return (0);
	if (!initialize_mlx(data))
	{
		close(fd);
		return (0);
	}
	if (!parse_config_and_map(fd, data))
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
