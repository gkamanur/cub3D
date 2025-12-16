/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_texture.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 10:40:21 by gkamanur          #+#    #+#             */
/*   Updated: 2025/12/16 10:47:45 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

static char	*get_texture_start(char *trimmed)
{
	if (ft_strncmp(trimmed, "NO ", 3) == 0
		|| ft_strncmp(trimmed, "SO ", 3) == 0
		|| ft_strncmp(trimmed, "WE ", 3) == 0
		|| ft_strncmp(trimmed, "EA ", 3) == 0)
		return (trimmed + 3);
	return (NULL);
}

int	validate_xpm_extension(const char *path)
{
	size_t	len;

	if (!path)
		return (0);
	len = 0;
	while (path[len])
		len++;
	if (len < 4)
		return (0);
	if (path[len - 4] != '.'
		|| path[len - 3] != 'x'
		|| path[len - 2] != 'p'
		|| path[len - 1] != 'm')
		return (0);
	return (1);
}
static char	*clean_texture_path(char *start)
{
	char	*path;
	size_t	len;

	while (*start && ft_isspace(*start))
		start++;
	if (*start == '\0')
		return (NULL);
	path = ft_strdup(start);
	if (!path)
		return (NULL);
	len = ft_strlen(path);
	while (len > 0 && (ft_isspace(path[len - 1]) || path[len - 1] == '.'))
	{
		path[len - 1] = '\0';
		len--;
	}
	if (len == 0)
	{
		free(path);
		return (NULL);
	}
	return (path);
}

char	*extract_texture_path(char *trimmed)
{
	char	*start;
	char	*path;

	start = get_texture_start(trimmed);
	if (!start)
		return (NULL);
	path = clean_texture_path(start);
	if (!path)
		return (NULL);
	if (!validate_xpm_extension(path))
	{
		free(path);
		return (NULL);
	}
	return (path);
}