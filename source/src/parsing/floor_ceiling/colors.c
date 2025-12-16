/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 13:26:40 by gkamanur          #+#    #+#             */
/*   Updated: 2025/12/16 10:35:06 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parsing.h"

int	extract_rgb(char *src, t_color *dst)
{
	if (!src || !dst)
		return (0);
	if (!check_rgb_format(src))
		return (0);
	return (parse_rgb(src, dst));
}

int	handle_floor(char *trimmed, t_color *floor)
{
	if (ft_strncmp(trimmed, "F ", 2) != 0)
		return (0);
	if (floor->r != -1 || floor->g != -1 || floor->b != -1)
		return (0);
	return (extract_rgb(trimmed + 2, floor));
}

int	handle_ceiling(char *trimmed, t_color *ceiling)
{
	if (ft_strncmp(trimmed, "C ", 2) != 0)
		return (0);
	if (ceiling->r != -1 || ceiling->g != -1 || ceiling->b != -1)
		return (0);
	return (extract_rgb(trimmed + 2, ceiling));
}

int	parse_color(char *line, t_color *floor, t_color *ceiling)
{
	char	*trimmed;
	int		ok;

	if (!line)
		return (0);
	trimmed = my_strtrim(line);
	if (!trimmed)
		return (0);
	ok = 0;
	if (ft_strncmp(trimmed, "F ", 2) == 0)
		ok = handle_floor(trimmed, floor);
	else if (ft_strncmp(trimmed, "C ", 2) == 0)
		ok = handle_ceiling(trimmed, ceiling);
	free(trimmed);
	return (ok);
}
