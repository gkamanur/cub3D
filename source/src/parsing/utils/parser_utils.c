/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 11:36:56 by gkamanur          #+#    #+#             */
/*   Updated: 2025/12/18 13:26:59 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parsing.h"

int	check_map_empty(t_map *map)
{
	if (!map->grid || map->width == 0 || map->height == 0)
	{
		printf("Error\nEmpty map\n");
		return (0);
	}
	return (1);
}

int	is_player_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

char	*my_strtrim(char *str)
{
	char	*start;
	char	*end;
	char	*result;
	int		len;

	if (!str)
		return (NULL);
	start = str;
	while (*start && ft_isspace(*start))
		start++;
	if (*start == '\0')
		return (ft_strdup(""));
	end = start + ft_strlen(start) - 1;
	while (end > start && ft_isspace(*end))
		end--;
	len = end - start + 1;
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	ft_strlcpy(result, start, len + 1);
	result[len] = '\0';
	return (result);
}

int	trim_line(char *line, char **trimmed)
{
	char	*tmp;

	tmp = ft_strtrim(line, " \t\n");
	if (!tmp)
		return (0);
	if (*tmp == '\0')
	{
		free(tmp);
		return (0);
	}
	*trimmed = tmp;
	return (1);
}
