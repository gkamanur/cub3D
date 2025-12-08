#include "../../../includes/parsing.h"

static int	config_complete(t_data *data)
{
	return (data->textures.north != NULL && data->textures.south != NULL
		&& data->textures.west != NULL && data->textures.east != NULL
		&& data->floor.r != -1 && data->ceiling.r != -1);
}

static int	handle_parse_result(int presult, char *trimmed, char *line)
{
	if (presult == 1)
	{
		free(trimmed);
		free(line);
		return (1);
	}
	if (presult == 0)
	{
		free(trimmed);
		free(line);
		printf("Error\nInvalid or duplicate config line\n");
		return (0);
	}
	return (0);
}

static int	handle_map_start(char *line, char *trimmed, t_data *data)
{
	(void)trimmed;
	data->map.first_line = line;
	return (2);
}

static int	parse_config_tokens(char *trimmed, t_data *data)
{
	if (ft_strncmp(trimmed, "NO ", 3) == 0 || ft_strncmp(trimmed, "SO ", 3) == 0
		|| ft_strncmp(trimmed, "WE ", 3) == 0 || ft_strncmp(trimmed, "EA ",
			3) == 0)
	{
		if (parse_texture(trimmed, &data->textures))
			return (1);
		return (0);
	}
	if (ft_strncmp(trimmed, "FT ", 3) == 0 || ft_strncmp(trimmed, "CT ",
			3) == 0)
	{
		if (parse_cf_texture(trimmed, &data->textures))
			return (1);
		return (0);
	}
	if (ft_strncmp(trimmed, "F ", 2) == 0 || ft_strncmp(trimmed, "C ", 2) == 0)
	{
		if (parse_color(trimmed, &data->floor, &data->ceiling))
			return (1);
		return (0);
	}
	return (-1);
}

int	parse_config(int fd, t_data *data, char *line)
{
	char	*trimmed;
	int		presult;

	while ((line = gnl(fd)) != NULL)
	{
		if (!trim_line(line, &trimmed))
			continue ;
		presult = parse_config_tokens(trimmed, data);
		if (presult != -1)
		{
			if (handle_parse_result(presult, trimmed, line) == 1)
				continue ;
			return (0);
		}
		if (config_complete(data))
		{
			handle_map_start(line, trimmed, data);
			break ;
		}
		printf("Error\nInvalid config line: %s\n", trimmed);
		free(trimmed);
		free(line);
		return (0);
	}
	return (1);
}
