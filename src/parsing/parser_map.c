#include "../../includes/parsing.h"

void	init_player_direction(t_player *player, char direction)
{
	if (direction == 'N')
	{
		player->dir_x = 0;
		player->dir_y = -1;
		player->plane_x = 0.66;
		player->plane_y = 0;
	}
	else if (direction == 'S')
	{
		player->dir_x = 0;
		player->dir_y = 1;
		player->plane_x = -0.66;
		player->plane_y = 0;
	}
	else if (direction == 'E')
	{
		player->dir_x = 1;
		player->dir_y = 0;
		player->plane_x = 0;
		player->plane_y = 0.66;
	}
	else if (direction == 'W')
	{
		player->dir_x = -1;
		player->dir_y = 0;
		player->plane_x = 0;
		player->plane_y = -0.66;
	}
}

// Check if line is part of map (contains valid map characters)
static int	is_map_line(char *line)
{
	int	i;

	if (!line || strlen(line) == 0)
		return (0);
	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '1' && line[i] != '0' &&
			line[i] != 'N' && line[i] != 'S' && line[i] != 'E' &&
			line[i] != 'W')
			return (0);
		i++;
	}
	return (1);
}

// Calculate max width of map
static int	get_max_width(char **lines, int count)
{
	int	max;
	int	len;
	int	i;

	max = 0;
	i = 0;
	while (i < count)
	{
		len = strlen(lines[i]);
		if (len > max)
			max = len;
		i++;
	}
	return (max);
}

// Pad line with spaces to match width
static char	*pad_line(char *line, int width)
{
	char	*padded;
	int		len;
	int		i;

	len = strlen(line);
	padded = malloc(width + 1);
	if (!padded)
		return (NULL);
	i = 0;
	while (i < len)
	{
		padded[i] = line[i];
		i++;
	}
	while (i < width)
	{
		padded[i] = ' ';
		i++;
	}
	padded[width] = '\0';
	return (padded);
}

// Parse map section from file
int	parse_map(int fd, t_data *data)
{
	char	*line;
	char	**temp_lines;
	int		count;
	int		i;

	temp_lines = malloc(sizeof(char *) * 1024);
	if (!temp_lines)
		return (0);
	count = 0;
	// Read all map lines
	while ((line = get_next_line(fd)) != NULL)
	{
		if (is_map_line(line))
		{
			temp_lines[count++] = line;
			if (count >= 1024)
				break;
		}
		else if (strlen(ft_strtrim(line)) > 0)
		{
			free(line);
			return (0); // Invalid line in map
		}
		else
			free(line);
	}
	if (count == 0)
	{
		free(temp_lines);
		return (0);
	}
	// Allocate map grid
	data->map.height = count;
	data->map.width = get_max_width(temp_lines, count);
	data->map.grid = malloc(sizeof(char *) * (count + 1));
	if (!data->map.grid)
	{
		while (count-- > 0)
			free(temp_lines[count]);
		free(temp_lines);
		return (0);
	}
	// Pad lines and copy to grid
	i = 0;
	while (i < count)
	{
		data->map.grid[i] = pad_line(temp_lines[i], data->map.width);
		free(temp_lines[i]);
		if (!data->map.grid[i])
		{
			while (i-- > 0)
				free(data->map.grid[i]);
			free(data->map.grid);
			free(temp_lines);
			return (0);
		}
		i++;
	}
	data->map.grid[count] = NULL;
	free(temp_lines);
	return (1);
}
