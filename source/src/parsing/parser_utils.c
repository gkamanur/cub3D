#include "../../includes/parsing.h"

// Simple get_next_line implementation for reading file line by line
char	*get_next_line(int fd)
{
	static char	buffer[4096];
	static int	buffer_pos = 0;
	static int	buffer_read = 0;
	char		line[4096];
	int			i;

	i = 0;
	while (1)
	{
		if (buffer_pos >= buffer_read)
		{
			buffer_read = read(fd, buffer, 4096);
			buffer_pos = 0;
			if (buffer_read <= 0)
				break ;
		}
		if (buffer[buffer_pos] == '\n')
		{
			buffer_pos++;
			break ;
		}
		line[i++] = buffer[buffer_pos++];
		if (i >= 4095)
			break ;
	}
	if (i == 0 && buffer_read <= 0)
		return (NULL);
	line[i] = '\0';
	return (strdup(line));
}

// Check if character is whitespace
int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r');
}

// Trim leading and trailing whitespace
char	*ft_strtrim(char *str)
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

// Split string by delimiter
char	**ft_split(char *str, char delimiter)
{
	char	**result;
	int		count;
	int		i;
	int		start;
	int		j;

	if (!str)
		return (NULL);
	// Count segments
	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] != delimiter && (i == 0 || str[i - 1] == delimiter))
			count++;
		i++;
	}
	result = malloc(sizeof(char *) * (count + 1));
	if (!result)
		return (NULL);
	// Extract segments
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != delimiter && (i == 0 || str[i - 1] == delimiter))
		{
			start = i;
			while (str[i] && str[i] != delimiter)
				i++;
			result[j] = malloc(i - start + 1);
			if (!result[j])
				return (NULL);
			strncpy(result[j], str + start, i - start);
			result[j][i - start] = '\0';
			j++;
		}
		else
			i++;
	}
	result[j] = NULL;
	return (result);
}
