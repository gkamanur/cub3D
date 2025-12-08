/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 13:26:40 by gkamanur          #+#    #+#             */
/*   Updated: 2025/12/08 15:18:06 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parsing.h"

int	extract_rgb(char *src, t_color *dst)
{
	char	*rgb_str;
	int		ok;

	rgb_str = my_strtrim(src);
	if (!rgb_str)
		return (0);
	ok = parse_rgb(rgb_str, dst);
	free(rgb_str);
	return (ok);
}

int	handle_floor(char *trimmed, t_color *floor)
{
	if (ft_strncmp(trimmed, "F ", 2) != 0)
		return (0);
	if (floor->r != -1)
		return (0);
	return (extract_rgb(trimmed + 2, floor));
}

int	handle_ceiling(char *trimmed, t_color *ceiling)
{
	if (ft_strncmp(trimmed, "C ", 2) != 0)
		return (0);
	if (ceiling->r != -1)
		return (0);
	return (extract_rgb(trimmed + 2, ceiling));
}
int	parse_color(char *line, t_color *floor, t_color *ceiling)
{
	char *trimmed;
	int result;

	trimmed = my_strtrim(line);
	if (!trimmed)
		return (0);
	result = handle_floor(trimmed, floor);
	if (!result)
		result = handle_ceiling(trimmed, ceiling);
	free(trimmed);
	return (result);
}