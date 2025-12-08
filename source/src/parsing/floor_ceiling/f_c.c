/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_c.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 17:24:55 by gkamanur          #+#    #+#             */
/*   Updated: 2025/12/08 15:57:54 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parsing.h"

// char	*ft_trim_line(char *line)
// {
// 	return (my_strtrim(line));
// }

char	**select_cf_destination(char *trimmed, t_textures *textures)
{
	if (ft_strncmp(trimmed, "FT ", 3) == 0 && !textures->floor_tex)
		return (&textures->floor_tex);
	if (ft_strncmp(trimmed, "CT ", 3) == 0 && !textures->ceiling_tex)
		return (&textures->ceiling_tex);
	return (NULL);
}

int	parse_cf_texture(char *line, t_textures *textures)
{
	char	*trimmed;
	char	*path;
	char	**dest;

	trim_line(line, &trimmed);
	if (!trimmed)
		return (0);
	dest = select_cf_destination(trimmed, textures);
	if (!dest)
	{
		free(trimmed);
		return (0);
	}
	path = my_strtrim(trimmed + 3);
	free(trimmed);
	if (!path || strlen(path) == 0)
	{
		free(path);
		return (0);
	}
	*dest = path;
	return (1);
}
