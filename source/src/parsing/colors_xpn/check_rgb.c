/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_rgb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 10:30:55 by gkamanur          #+#    #+#             */
/*   Updated: 2025/12/16 14:44:52 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parsing.h"

void	free_split(char **res)
{
	int	i;

	i = 0;
	if (!res)
		return ;
	while (res[i])
		free(res[i++]);
	free(res);
}

static int	is_valid_rgb_value(char *str)
{
	int	val;

	if (!str)
		return (0);
	if (ft_strlen(str) > 3)
		return (0);
	val = ft_atoi(str);
	if (val < 0 || val > 255)
		return (0);
	return (1);
}

static int	validate_rgb_array(char **colors)
{
	int	i;

	i = 0;
	while (colors[i])
		i++;
	if (i != 3)
		return (0);
	i = 0;
	while (i < 3)
	{
		if (!is_valid_rgb_value(colors[i]))
			return (0);
		i++;
	}
	return (1);
}

int	check_rgb_format(char *src)
{
	char	**colors;
	int		valid;

	if (!src)
		return (0);
	colors = ft_split(src, ',');
	if (!colors)
		return (0);
	valid = validate_rgb_array(colors);
	free_split(colors);
	return (valid);
}
