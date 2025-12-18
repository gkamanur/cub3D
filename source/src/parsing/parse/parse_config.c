/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 15:15:31 by gkamanur          #+#    #+#             */
/*   Updated: 2025/12/18 13:43:34 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parsing.h"

// static int	process_config_line(char *line, t_data *data)
// {
// 	char	*trimmed;
// 	int		presult;

// 	if (!trim_line(line, &trimmed))
// 	{
// 		free(line);
// 		return(1);
// 	}
// 	presult = parse_config_tokens(trimmed, data);
// 	if (presult == 1)
// 	{
// 		free(trimmed);
// 		free(line);
// 		return (1);
// 	}
// 	if (presult == 0)
// 	{
// 		printf("Error\nInvalid or duplicate config line\n");
// 		free(trimmed);
// 		free(line);
// 		return (0);
// 	}
// 	if (config_complete(data))
// 	{
// 		handle_map_start(line, data);
// 		free(trimmed);
// 		return (2);
// 	}
// 	printf("Error config line: %s\n", trimmed);
// 	free(trimmed);
// 	free(line);
// 	return (0);
// }

static int	handle_parse_result(int presult, char *trimmed, char *line, t_data *data)
{
	if (presult == 1)
	{
		free(trimmed);
		free(line);
		return (1);
	}
	if (presult == 0)
	{
		printf("Error\nInvalid or duplicate config line\n");
		free(trimmed);
		free(line);
		return (0);
	}
	if (config_complete(data))
	{
		handle_map_start(line, data);
		free(trimmed);
		return (2);
	}
	return (-1);
}

static int	process_config_line(char *line, t_data *data)
{
	char	*trimmed;
	int		presult;
	int		res;

	if (!trim_line(line, &trimmed))
	{
		free(line);
		return (1);
	}

	presult = parse_config_tokens(trimmed, data);
	res = handle_parse_result(presult, trimmed, line, data);
	if (res != -1)
		return (res);

	printf("Error config line: %s\n", trimmed);
	free(trimmed);
	free(line);
	return (0);
}

int	parse_config(int fd, t_data *data, char *line)
{
	int	result;

	(void)line;
	while ((line = gnl(fd)))
	{
		result = process_config_line(line, data);
		if (result == 1)
			continue ;
		if (result == 2)
			return (1);
		return (0);
	}
	return (1);
}
