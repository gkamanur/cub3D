/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 15:00:56 by gkamanur          #+#    #+#             */
/*   Updated: 2025/12/17 10:13:18 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parsing.h"

static char	**detect_texture_target(char *trimmed, t_textures *t)
{
	if (ft_strncmp(trimmed, "NO ", 3) == 0 && !t->north)
		return (&t->north);
	if (ft_strncmp(trimmed, "SO ", 3) == 0 && !t->south)
		return (&t->south);
	if (ft_strncmp(trimmed, "WE ", 3) == 0 && !t->west)
		return (&t->west);
	if (ft_strncmp(trimmed, "EA ", 3) == 0 && !t->east)
		return (&t->east);
	return (NULL);
}

// static int	assign_texture(char **dest, char *path)
// {
// 	if (!path || ft_strlen(path) == 0)
// 	{
// 		// if (path)
// 		// 	free(path);
// 		return (0);
// 	}
// 	*dest = path;
// 	return (1);
// }

int	parse_texture(char *line, t_textures *textures)
{
	char	*trimmed;
	char	**dest;
	char	*path;

	trimmed = my_strtrim(line);
	if (!trimmed)
		return (0);
	dest = detect_texture_target(trimmed, textures);
	if (!dest)
		return (free(trimmed), 0);
	path = extract_texture_path(trimmed);
	free(trimmed);
	if (!path)
		return (0);
	// return (assign_texture(dest, path));
	*dest = path;
	return(1);
}
