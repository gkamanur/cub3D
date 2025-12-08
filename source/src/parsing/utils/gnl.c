/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 15:38:32 by gkamanur          #+#    #+#             */
/*   Updated: 2025/12/08 15:14:43 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../../includes/parsing.h"

static int	refill_buffer(int fd, t_gnl_data *data)
{
	data->buffer_read = read(fd, data->buffer, BUFFER_SIZE);
	if (data->buffer_read < 0)
		return (0);
	data->buffer_pos = 0;
	return (1);
}

static int	check_and_refill_buffer(int fd, t_gnl_data *data)
{
	if (data->buffer_pos >= data->buffer_read)
	{
		if (!refill_buffer(fd, data))
			return (0);
		if (data->buffer_read <= 0)
		{
			data->eof = 1;
			return (0);
		}
	}
	return (1);
}

static int	copy_to_line(t_gnl_data *data, char *line, int *line_index)
{
	if (data->buffer[data->buffer_pos] == '\n')
	{
		data->buffer_pos++;
		return (1);
	}
	if (*line_index >= BUFFER_SIZE)
		return (1);
	line[(*line_index)++] = data->buffer[data->buffer_pos++];
	return (0);
}

static char	*create_line(char *line, int line_index, int eof)
{
	char	*result;

	if (line_index == 0 && eof)
		return (NULL);
	line[line_index] = '\0';
	result = ft_strdup(line);
	if (!result)
		return (NULL);
	return (result);
}

char	*gnl(int fd)
{
	static t_gnl_data	data;
	char				line[BUFFER_SIZE + 1];
	int					line_index;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (data.buffer_read == 0)
    {
		data.buffer_pos = 0;
	    data.buffer_read = 0;
	    data.eof = 0;
    }
	line_index = 0;
	while (1)
	{
		if (!check_and_refill_buffer(fd, &data))
			break ;
		if (copy_to_line(&data, line, &line_index))
			break ;
	}
	return (create_line(line, line_index, data.eof));
}
