/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 15:15:31 by gkamanur          #+#    #+#             */
/*   Updated: 2025/12/16 15:16:31 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parsing.h"

static int	process_config_line(char *line, t_data *data)
{
	char	*trimmed;
	int		presult;

	if (!trim_line(line, &trimmed))
		return (1);
	presult = parse_config_tokens(trimmed, data);
	if (presult != -1)
	{
		return (handle_parse_result(presult, trimmed, line));
	}
	if (config_complete(data))
	{
		handle_map_start(line, data);
		free(trimmed);
		return (2);
	}
	printf("Error config line: %s\n", trimmed);
	free(trimmed);
	free(line);
	return (0);
}

int	parse_config(int fd, t_data *data, char *line)
{
	int	result;

	line = gnl(fd);
	while (line != NULL)
	{
		result = process_config_line(line, data);
		if (result == 1)
			continue ;
		else if (result == 2)
			break ;
		else if (result == 0)
			return (0);
		line = gnl(fd);
	}
	return (1);
}
