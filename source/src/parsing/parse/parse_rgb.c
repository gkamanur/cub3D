/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rgb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 17:38:40 by gkamanur          #+#    #+#             */
/*   Updated: 2025/12/04 17:42:14 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

static int	count_parts(char **parts)
{
	int	i;

	i = 0;
	while (parts[i])
		i++;
	return (i);
}

static void	free_parts(char **parts, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		free(parts[i]);
		i++;
	}
	free(parts);
}

static int	assign_and_validate(char **parts, t_color *color)
{
	color->r = ft_atoi(parts[0]);
	color->g = ft_atoi(parts[1]);
	color->b = ft_atoi(parts[2]);
	if (color->r < 0 || color->r > 255 || color->g < 0 || color->g > 255
		|| color->b < 0 || color->b > 255)
		return (0);
	return (1);
}

int	parse_rgb(char *str, t_color *color)
{
	char	**parts;
	int		n;
	int		ok;

	parts = ft_split(str, ',');
	if (!parts)
		return (0);
	n = count_parts(parts);
	if (n != 3)
	{
		while (n-- > 0)
			free(parts[n]);
		free(parts);
		return (0);
	}
	ok = assign_and_validate(parts, color);
	free_parts(parts, 3);
	return (ok);
}
