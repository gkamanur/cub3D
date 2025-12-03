/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 14:11:59 by gkamanur          #+#    #+#             */
/*   Updated: 2025/12/03 14:21:54 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rendering.h"

typedef struct s_minimap
{
	int	scale;
	int	offset_x;
	int	offset_y;
}	t_minimap;

static int	get_minimap_color(t_data *data, int map_x, int map_y)
{
	char	cell;

	cell = data->map.grid[map_y][map_x];
	if (cell == '1')
		return (0xFFFFFF);
	else if (cell == '0')
		return (0x333333);
	else
		return (0x000000);
}

static void	draw_minimap_cell(t_data *data, int map_x, int map_y, t_minimap *mm)
{
	int	color;
	int	screen_y;
	int	screen_x;

	color = get_minimap_color(data, map_x, map_y);
	screen_y = 0;
	while (screen_y < mm->scale)
	{
		screen_x = 0;
		while (screen_x < mm->scale)
		{
			put_pixel_to_img(&data->img, mm->offset_x + map_x * mm->scale + screen_x,
				mm->offset_y + map_y * mm->scale + screen_y, color);
			screen_x++;
		}
		screen_y++;
	}
}

static void	draw_minimap_grid(t_data *data, t_minimap *mm)
{
	int	map_y;
	int	map_x;

	map_y = 0;
	while (map_y < data->map.height)
	{
		map_x = 0;
		while (map_x < data->map.width)
		{
			draw_minimap_cell(data, map_x, map_y, mm);
			map_x++;
		}
		map_y++;
	}
}

static void	draw_player_dot(t_data *data, t_minimap *mm)
{
	int	screen_x;
	int	screen_y;
	int	dot_size;
	int	dy;
	int	dx;

	screen_x = mm->offset_x + (int)(data->player.x * mm->scale);
	screen_y = mm->offset_y + (int)(data->player.y * mm->scale);
	dot_size = 3;
	dy = -dot_size;
	while (dy <= dot_size)
	{
		dx = -dot_size;
		while (dx <= dot_size)
		{
			if (dx * dx + dy * dy <= dot_size * dot_size)
			{
				put_pixel_to_img(&data->img, screen_x + dx,
					screen_y + dy, 0xFF0000);
			}
			dx++;
		}
		dy++;
	}
}

static void	draw_player_direction(t_data *data, t_minimap *mm)
{
	int	screen_x;
	int	screen_y;
	int	dir_length;
	int	i;

	screen_x = mm->offset_x + (int)(data->player.x * mm->scale);
	screen_y = mm->offset_y + (int)(data->player.y * mm->scale);
	dir_length = 15;
	i = 0;
	while (i < dir_length)
	{
		put_pixel_to_img(&data->img, screen_x + (int)(data->player.dir_x * i),
			screen_y + (int)(data->player.dir_y * i), 0xFFFF00);
		i++;
	}
}

void	draw_minimap(t_data *data)
{
	t_minimap	mm;

	mm.scale = 10;
	mm.offset_x = WIN_WIDTH - (data->map.width * mm.scale) - 20;
	mm.offset_y = 20;
	draw_minimap_grid(data, &mm);
	draw_player_dot(data, &mm);
	draw_player_direction(data, &mm);
}
