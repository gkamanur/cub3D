#include "../../../includes/parsing.h"

int	check_texture_file(char *path, const char *label)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		printf("Error\nCannot open %s texture: %s\n", label, path);
		return (0);
	}
	close(fd);
	return (1);
}

int	check_texture_paths(t_textures *textures)
{
	if (!textures->north || !textures->south || !textures->west
		|| !textures->east)
	{
		printf("Error\nMissing texture paths\n");
		return (0);
	}
	return (1);
}

int	validate_textures(t_textures *textures)
{
	if (!check_texture_paths(textures))
		return (0);
	if (!check_texture_file(textures->north, "north"))
		return (0);
	if (!check_texture_file(textures->south, "south"))
		return (0);
	if (!check_texture_file(textures->west, "west"))
		return (0);
	if (!check_texture_file(textures->east, "east"))
		return (0);
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
int	check_borders(char **grid, int width, int height)
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






