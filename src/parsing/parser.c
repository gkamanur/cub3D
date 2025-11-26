#include "../../includes/parsing.h"

// Initialize data structure with default values
static void	init_data(t_data *data)
{
	data->mlx_ptr = NULL;
	data->win_ptr = NULL;
	data->textures.north = NULL;
	data->textures.south = NULL;
	data->textures.west = NULL;
	data->textures.east = NULL;
	data->floor.r = -1;
	data->floor.g = -1;
	data->floor.b = -1;
	data->ceiling.r = -1;
	data->ceiling.g = -1;
	data->ceiling.b = -1;
	data->map.grid = NULL;
	data->map.width = 0;
	data->map.height = 0;
	data->player.x = 0;
	data->player.y = 0;
	data->player.dir_x = 0;
	data->player.dir_y = 0;
	data->player.plane_x = 0;
	data->player.plane_y = 0;
}

// Check if all config elements have been parsed
static int	config_complete(t_data *data)
{
	return (data->textures.north != NULL &&
			data->textures.south != NULL &&
			data->textures.west != NULL &&
			data->textures.east != NULL &&
			data->floor.r != -1 &&
			data->ceiling.r != -1);
}

// Parse config section (textures and colors)
static int	parse_config(int fd, t_data *data)
{
	char	*line;
	char	*trimmed;
	int		result;

	while ((line = get_next_line(fd)) != NULL)
	{
		trimmed = ft_strtrim(line);
		if (!trimmed)
		{
			free(line);
			continue;
		}
		// Skip empty lines
		if (strlen(trimmed) == 0)
		{
			free(trimmed);
			free(line);
			continue;
		}
		// Try to parse as texture or color
		result = 0;
		if (strncmp(trimmed, "NO ", 3) == 0 || strncmp(trimmed, "SO ", 3) == 0 ||
			strncmp(trimmed, "WE ", 3) == 0 || strncmp(trimmed, "EA ", 3) == 0)
			result = parse_texture(trimmed, &data->textures);
		else if (strncmp(trimmed, "F ", 2) == 0 || strncmp(trimmed, "C ", 2) == 0)
			result = parse_color(trimmed, &data->floor, &data->ceiling);
		else
		{
			// Not a config line, might be start of map
			free(trimmed);
			free(line);
			break;
		}
		free(trimmed);
		free(line);
		if (!result)
		{
			printf("Error\nInvalid or duplicate config line\n");
			return (0);
		}
		// Check if config is complete
		if (config_complete(data))
			break;
	}
	return (1);
}

// Main parser function
int	parse_cub_file(char *filename, t_data *data)
{
	int	fd;
	int	len;

	// Check file extension
	len = strlen(filename);
	if (len < 4 || strcmp(filename + len - 4, ".cub") != 0)
	{
		printf("Error\nFile must have .cub extension\n");
		return (0);
	}
	// Open file
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		printf("Error\nCannot open file: %s\n", filename);
		return (0);
	}
	// Initialize data
	init_data(data);
	// Parse config section
	if (!parse_config(fd, data))
	{
		close(fd);
		return (0);
	}
	// Validate config
	if (!validate_textures(&data->textures) || 
		!validate_colors(&data->floor, &data->ceiling))
	{
		close(fd);
		return (0);
	}
	// Parse map section
	if (!parse_map(fd, data))
	{
		printf("Error\nInvalid map\n");
		close(fd);
		return (0);
	}
	close(fd);
	// Validate map
	if (!validate_map(&data->map, &data->player))
		return (0);
	printf("✓ Map parsed successfully\n");
	printf("  Map size: %dx%d\n", data->map.width, data->map.height);
	printf("  Player at: (%.1f, %.1f)\n", data->player.x, data->player.y);
	return (1);
}
