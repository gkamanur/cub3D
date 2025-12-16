/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_xpm_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 10:43:51 by gkamanur          #+#    #+#             */
/*   Updated: 2025/12/16 10:44:12 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

static int	validate_xpm_string(const char *path)
{
	const char	*ptr;
	size_t		len;

	if (!path)
		return (0);
	ptr = path;
	len = 0;
	while (*ptr)
	{
		if (*ptr == ' ' || *ptr == '\t' || *ptr == '\n')
			return (0);
		ptr++;
		len++;
	}
	if (len < 4)
		return (0);
	if (ptr[-4] != '.' || ptr[-3] != 'x'
		|| ptr[-2] != 'p' || ptr[-1] != 'm')
		return (0);
	return (1);
}

static int	validate_xpm_image(void *mlx_ptr, const char *path)
{
	int		fd;
	int		width;
	int		height;
	void	*img;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	img = mlx_xpm_file_to_image(mlx_ptr, (char *)path, &width, &height);
	if (!img)
		return (0);
	if (width <= 0 || height <= 0 || width > 4096 || height > 4096)
	{
		mlx_destroy_image(mlx_ptr, img);
		return (0);
	}
	mlx_destroy_image(mlx_ptr, img);
	return (1);
}

int	validate_xpm_path(void *mlx_ptr, const char *path)
{
	if (!mlx_ptr || !path)
		return (0);
	if (!validate_xpm_string(path))
		return (0);
	if (!validate_xpm_image(mlx_ptr, path))
		return (0);
	return (1);
}


