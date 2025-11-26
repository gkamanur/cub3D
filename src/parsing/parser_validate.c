#include "../../includes/parsing.h"

// Check if texture files exist and are valid
int	validate_textures(t_textures *textures)
{
	int	fd;

	if (!textures->north || !textures->south || 
		!textures->west || !textures->east)
	{
		printf("Error\nMissing texture paths\n");
		return (0);
	}
	// Check if files exist
	fd = open(textures->north, O_RDONLY);
	if (fd < 0)
	{
		printf("Error\nCannot open north texture: %s\n", textures->north);
		return (0);
	}
	close(fd);
	fd = open(textures->south, O_RDONLY);
	if (fd < 0)
	{
		printf("Error\nCannot open south texture: %s\n", textures->south);
		return (0);
	}
	close(fd);
	fd = open(textures->west, O_RDONLY);
	if (fd < 0)
	{
		printf("Error\nCannot open west texture: %s\n", textures->west);
		return (0);
	}
	close(fd);
	fd = open(textures->east, O_RDONLY);
	if (fd < 0)
	{
		printf("Error\nCannot open east texture: %s\n", textures->east);
		return (0);
	}
	close(fd);
	return (1);
}

// Validate floor and ceiling colors
int	validate_colors(t_color *floor, t_color *ceiling)
{
	if (floor->r == -1 || floor->g == -1 || floor->b == -1)
	{
		printf("Error\nMissing floor color\n");
		return (0);
	}
	if (ceiling->r == -1 || ceiling->g == -1 || ceiling->b == -1)
	{
		printf("Error\nMissing ceiling color\n");
		return (0);
	}
	return (1);
}

// Check if map borders are all walls
static int	check_borders(char **grid, int width, int height)
{
	int	x;
	int	y;

	// Check top and bottom
	x = 0;
	while (x < width)
	{
		if (grid[0][x] != '1' && grid[0][x] != ' ')
			return (0);
		if (grid[height - 1][x] != '1' && grid[height - 1][x] != ' ')
			return (0);
		x++;
	}
	// Check left and right
	y = 0;
	while (y < height)
	{
		if (grid[y][0] != '1' && grid[y][0] != ' ')
			return (0);
		if (grid[y][width - 1] != '1' && grid[y][width - 1] != ' ')
			return (0);
		y++;
	}
	return (1);
}

// Validate map and find player position
int	validate_map(t_map *map, t_player *player)
{
	int		x;
	int		y;
	int		player_count;
	char	player_dir;

	if (!map->grid || map->width == 0 || map->height == 0)
	{
		printf("Error\nEmpty map\n");
		return (0);
	}
	// Find player position
	player_count = 0;
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->grid[y][x] == 'N' || map->grid[y][x] == 'S' ||
				map->grid[y][x] == 'E' || map->grid[y][x] == 'W')
			{
				player_count++;
				player->x = x + 0.5;
				player->y = y + 0.5;
				player_dir = map->grid[y][x];
				map->grid[y][x] = '0'; // Replace with floor
			}
			x++;
		}
		y++;
	}
	if (player_count != 1)
	{
		printf("Error\nMap must have exactly one player\n");
		return (0);
	}
	// Initialize player direction
	init_player_direction(player, player_dir);
	// Check if borders are valid
	if (!check_borders(map->grid, map->width, map->height))
	{
		printf("Error\nMap not surrounded by walls\n");
		return (0);
	}
	return (1);
}
