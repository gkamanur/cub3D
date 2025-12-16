/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 15:01:44 by gkamanur          #+#    #+#             */
/*   Updated: 2025/12/15 13:54:29 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parsing.h"

void	set_player_position(t_player *player, int x, int y, char c, char *dir)
{
	player->x = x + 0.5;
	player->y = y + 0.5;
	*dir = c;
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
				set_player_position(player, x, y, c, player_dir);
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

int	validate_map(t_map *map, t_player *player)
{
	char	player_dir;
	int		player_count;
	t_map_extents extents;
	
	if (!check_map_empty(map))
		return (0);
	player_count = find_player(map, player, &player_dir);
	if (!validate_player_count(player_count))
		return (0);
	init_player_direction(player, player_dir);
	extents = compute_row_extents(map->grid, map->height);
	if (!extents.rows)
	{
		printf("Error\nFailed to compute map extents\n");
		return (0);
	}
	if (!check_no_empty_rows(&extents))
	{
		free_row_extents(&extents);
		printf("Error\nMap has empty rows or columns\n");
		return (0);
	}
	if (!check_no_empty_columns(map->grid, &extents, map->width))
	{
		free_row_extents(&extents);
		printf("Error\nMap has empty rows or columns\n");
		return (0);
	}
	if (!check_borders_strict(map->grid, map->width, map->height))
	{
		free_row_extents(&extents);
		printf("Error\nMap not surrounded by walls\n");
		return (0);
	}
	free_row_extents(&extents);
	return (1);
}

// static int check_map_basic(t_map *map)
// {
//     if (!check_map_empty(map))
//         return 0;
//     return 1;
// }

// // Helper: find and initialize the player
// static int check_and_init_player(t_map *map, t_player *player)
// {
//     char player_dir;
//     int player_count;

//     player_count = find_player(map, player, &player_dir);
//     if (!validate_player_count(player_count))
//         return 0;

//     init_player_direction(player, player_dir);
//     return 1;
// }

// // Helper: check extents (rows and columns)
// static int check_map_extents(t_map *map)
// {
//     t_map_extents extents;

//     extents = compute_row_extents(map->grid, map->height);
//     if (!extents.rows)
//     {
//         printf("Error\nFailed to compute map extents\n");
//         return 0;
//     }

//     if (!check_no_empty_rows(&extents) || !check_no_empty_columns(map->grid, &extents, map->width))
//     {
//         free_row_extents(&extents);
//         printf("Error\nMap has empty rows or columns\n");
//         return 0;
//     }

//     free_row_extents(&extents);
//     return 1;
// }

// // Helper: check map borders
// static int check_map_borders(t_map *map)
// {
//     if (!check_borders_strict(map->grid, map->width, map->height))
//     {
//         printf("Error\nMap not surrounded by walls\n");
//         return 0;
//     }
//     return 1;
// }

// // Main validation function
// int validate_map(t_map *map, t_player *player)
// {
//     if (!check_map_basic(map))
//         return 0;
//     if (!check_and_init_player(map, player))
//         return 0;
//     if (!check_map_extents(map))
//         return 0;
//     if (!check_map_borders(map))
//         return 0;
//     return 1;
// }