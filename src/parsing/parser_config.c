#include "../../includes/parsing.h"

// Parse RGB color from string "220,100,0"
static int	parse_rgb(char *str, t_color *color)
{
	char	**parts;
	int		i;

	parts = ft_split(str, ',');
	if (!parts)
		return (0);
	// Count parts
	i = 0;
	while (parts[i])
		i++;
	if (i != 3)
	{
		while (i-- > 0)
			free(parts[i]);
		free(parts);
		return (0);
	}
	color->r = atoi(parts[0]);
	color->g = atoi(parts[1]);
	color->b = atoi(parts[2]);
	// Free parts
	for (i = 0; i < 3; i++)
		free(parts[i]);
	free(parts);
	// Validate range
	if (color->r < 0 || color->r > 255 ||
		color->g < 0 || color->g > 255 ||
		color->b < 0 || color->b > 255)
		return (0);
	return (1);
}

// Parse texture line: "NO ./textures/north.xpm"
int	parse_texture(char *line, t_textures *textures)
{
	char	*trimmed;
	char	*path;
	char	**dest;

	trimmed = ft_strtrim(line);
	if (!trimmed)
		return (0);
	// Determine which texture
	dest = NULL;
	if (strncmp(trimmed, "NO ", 3) == 0 && !textures->north)
	{
		dest = &textures->north;
		path = ft_strtrim(trimmed + 3);
	}
	else if (strncmp(trimmed, "SO ", 3) == 0 && !textures->south)
	{
		dest = &textures->south;
		path = ft_strtrim(trimmed + 3);
	}
	else if (strncmp(trimmed, "WE ", 3) == 0 && !textures->west)
	{
		dest = &textures->west;
		path = ft_strtrim(trimmed + 3);
	}
	else if (strncmp(trimmed, "EA ", 3) == 0 && !textures->east)
	{
		dest = &textures->east;
		path = ft_strtrim(trimmed + 3);
	}
	else
	{
		free(trimmed);
		return (0);
	}
	free(trimmed);
	if (!path || strlen(path) == 0)
	{
		if (path)
			free(path);
		return (0);
	}
	*dest = path;
	return (1);
}

// Parse color line: "F 220,100,0" or "C 225,30,0"
int	parse_color(char *line, t_color *floor, t_color *ceiling)
{
	char	*trimmed;
	char	*rgb_str;
	int		result;

	trimmed = ft_strtrim(line);
	if (!trimmed)
		return (0);
	result = 0;
	if (strncmp(trimmed, "F ", 2) == 0 && floor->r == -1)
	{
		rgb_str = ft_strtrim(trimmed + 2);
		if (rgb_str && parse_rgb(rgb_str, floor))
			result = 1;
		if (rgb_str)
			free(rgb_str);
	}
	else if (strncmp(trimmed, "C ", 2) == 0 && ceiling->r == -1)
	{
		rgb_str = ft_strtrim(trimmed + 2);
		if (rgb_str && parse_rgb(rgb_str, ceiling))
			result = 1;
		if (rgb_str)
			free(rgb_str);
	}
	free(trimmed);
	return (result);
}
