/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 15:01:44 by gkamanur          #+#    #+#             */
/*   Updated: 2025/12/17 09:47:36 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parsing.h"

char	set_player_position(t_player *player, int x, int y, char c)
{
	player->x = x + 0.5;
	player->y = y + 0.5;
	return (c);
}

int	scan_map_for_player(t_map *map, t_player *player, char *player_dir)
{
	int		x;
	int		y;
	int		count;
	char	c;

	count = 0;
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			c = map->grid[y][x];
			if (is_player_char(c))
			{
				count++;
				*player_dir = set_player_position(player, x, y, c);
				map->grid[y][x] = '0';
			}
			x++;
		}
		y++;
	}
	return (count);
}

int	find_player(t_map *map, t_player *player, char *player_dir)
{
	*player_dir = 'N';
	return (scan_map_for_player(map, player, player_dir));
}

int	validate_player_count(int player_count)
{
	if (player_count != 1)
	{
		printf("Error\nMap must have exactly one player\n");
		return (0);
	}
	return (1);
}
