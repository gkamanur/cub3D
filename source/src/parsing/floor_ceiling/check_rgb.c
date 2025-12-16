/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_rgb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 10:30:55 by gkamanur          #+#    #+#             */
/*   Updated: 2025/12/16 10:33:20 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parsing.h"

static int	handle_rgb_char(char c, int *value_count, int *in_number)
{
	if (ft_isdigit(c))
	{
		if (!*in_number)
		{
			(*value_count)++;
			*in_number = 1;
			if (*value_count > 3)
				return (0);
		}
	}
	else if (c == ',')
	{
		if (!*in_number || *value_count >= 3)
			return (0);
		*in_number = 0;
	}
	else if (c == ' ' || c == '\t')
	{
		if (*in_number)
			*in_number = 0;
	}
	else
		return (0);
	return (1);
}

static int	parse_rgb_format(char *src, int *value_count)
{
	int	i;
	int	in_number;

	i = 0;
	in_number = 0;
	while (src[i])
	{
		if (!handle_rgb_char(src[i], value_count, &in_number))
			return (0);
		i++;
	}
	return (1);
}

int	check_rgb_format(char *src)
{
	int	value_count;

	if (!src)
		return (0);
	value_count = 0;
	if (!parse_rgb_format(src, &value_count))
		return (0);
	return (value_count == 3);
}
