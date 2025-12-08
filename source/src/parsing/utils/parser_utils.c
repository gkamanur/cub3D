#include "../../../includes/parsing.h"



int	check_map_empty(t_map *map)
{
	if (!map->grid || map->width == 0 || map->height == 0)
	{
		printf("Error\nEmpty map\n");
		return (0);
	}
	return (1);
}

int	is_player_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

char	*my_strtrim(char *str)
{
	char	*start;
	char	*end;
	char	*result;
	int		len;

	if (!str)
		return (NULL);
	start = str;
	while (*start && ft_isspace(*start))
		start++;
	if (*start == '\0')
		return (strdup(""));
	end = start + strlen(start) - 1;
	while (end > start && ft_isspace(*end))
		end--;
	len = end - start + 1;
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	strncpy(result, start, len);
	result[len] = '\0';
	return (result);
}

int	trim_line(char *line, char **trimmed_out)
{
	char	*trimmed;

	trimmed = my_strtrim(line);
	if (!trimmed)
	{
		free(line);
		return (0);
	}
	if (ft_strlen(trimmed) == 0)
	{
		free(trimmed);
		free(line);
		return (0);
	}
	*trimmed_out = trimmed;
	return (1);
}
