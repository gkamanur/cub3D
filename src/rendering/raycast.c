/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 13:52:27 by gkamanur          #+#    #+#             */
/*   Updated: 2025/12/03 14:23:28 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

typedef struct s_ray
{
	double		camera_x;
	double		ray_dir_x;
	double		ray_dir_y;
	int			map_x;
	int			map_y;
	double		side_dist_x;
	double		side_dist_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		perp_wall_dist;
	int			step_x;
	int			step_y;
	int			hit;
	int			side;
}				t_ray;

typedef struct s_draw_info
{
	int			line_height;
	int			draw_start;
	int			draw_end;
	double		wall_x;
	int			tex_x;
	double		step;
	double		tex_pos;
}				t_draw_info;


int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

static void	init_ray_values(t_data *data, int x, t_ray *ray)
{
	ray->camera_x = 2 * x / (double)WIN_WIDTH - 1;
	ray->ray_dir_x = data->player.dir_x + data->player.plane_x * ray->camera_x;
	ray->ray_dir_y = data->player.dir_y + data->player.plane_y * ray->camera_x;
	ray->map_x = (int)data->player.x;
	ray->map_y = (int)data->player.y;
	
	// FIXED: Prevent division by zero
	if (ray->ray_dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	if (ray->ray_dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
	
	ray->hit = 0;
}

static void	calculate_step_and_side_dist(t_data *data, t_ray *ray)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (data->player.x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - data->player.x)
			* ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (data->player.y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - data->player.y)
			* ray->delta_dist_y;
	}
}

static void	perform_dda(t_data *data, t_ray *ray)
{
	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (ray->map_x < 0 || ray->map_x >= data->map.width
			|| ray->map_y < 0 || ray->map_y >= data->map.height
			|| data->map.grid[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
	}
}

static void	calculate_wall_distance(t_data *data, t_ray *ray)
{
	if (ray->side == 0)
	{
		ray->perp_wall_dist = (ray->map_x - data->player.x
				+ (1 - ray->step_x) / 2) / ray->ray_dir_x;
	}
	else
	{
		ray->perp_wall_dist = (ray->map_y - data->player.y
				+ (1 - ray->step_y) / 2) / ray->ray_dir_y;
	}
	// FIXED: Prevent negative or zero distance
	if (ray->perp_wall_dist <= 0)
		ray->perp_wall_dist = 0.0001;
}

static void	init_draw_info(t_data *data, t_ray *ray, t_draw_info *draw)
{
	draw->line_height = (int)(WIN_HEIGHT / ray->perp_wall_dist);
	draw->draw_start = -draw->line_height / 2 + WIN_HEIGHT / 2;
	if (draw->draw_start < 0)
		draw->draw_start = 0;
	draw->draw_end = draw->line_height / 2 + WIN_HEIGHT / 2;
	if (draw->draw_end >= WIN_HEIGHT)
		draw->draw_end = WIN_HEIGHT - 1;
	if (ray->side == 0)
		draw->wall_x = data->player.y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		draw->wall_x = data->player.x + ray->perp_wall_dist * ray->ray_dir_x;
	draw->wall_x -= floor(draw->wall_x);
}

static t_img	*get_wall_texture(t_data *data, t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->ray_dir_x > 0)
			return (&data->textures.east_img);
		else
			return (&data->textures.west_img);
	}
	else
	{
		if (ray->ray_dir_y > 0)
			return (&data->textures.south_img);
		else
			return (&data->textures.north_img);
	}
}

static void	calculate_texture_x(t_img *texture, t_ray *ray,
								t_draw_info *draw)
{
	draw->tex_x = (int)(draw->wall_x * (double)texture->width);
	if ((ray->side == 0 && ray->ray_dir_x > 0)
		|| (ray->side == 1 && ray->ray_dir_y < 0))
		draw->tex_x = texture->width - draw->tex_x - 1;
	if (draw->tex_x < 0)
		draw->tex_x = 0;
	else if (draw->tex_x >= texture->width)
		draw->tex_x = texture->width - 1;
}

static void	draw_textured_column(t_data *data, int x, t_draw_info *draw,
									t_img *texture)
{
	int	y;
	int	tex_y;
	int	color;

	y = draw->draw_start;
	while (y < draw->draw_end)
	{
		tex_y = (int)draw->tex_pos;
		if (tex_y < 0)
			tex_y = 0;
		else if (tex_y >= texture->height)
			tex_y = texture->height - 1;
		draw->tex_pos += draw->step;
		color = get_texture_pixel(texture, draw->tex_x, tex_y);
		put_pixel_to_img(&data->img, x, y, color);
		y++;
	}
}

static void	cast_single_ray(t_data *data, int x)
{
	t_ray		ray;
	t_draw_info	draw;
	t_img		*texture;

	init_ray_values(data, x, &ray);
	calculate_step_and_side_dist(data, &ray);
	perform_dda(data, &ray);
	calculate_wall_distance(data, &ray);
	init_draw_info(data, &ray, &draw);
	texture = get_wall_texture(data, &ray);
	calculate_texture_x(texture, &ray, &draw);
	draw.step = (double)texture->height / draw.line_height;
	draw.tex_pos = (draw.draw_start - WIN_HEIGHT / 2
			+ draw.line_height / 2) * draw.step;
	draw_textured_column(data, x, &draw, texture);
}

static void	draw_floor_ceiling(t_data *data)
{
	int	x;
	int	y;
	int	floor_color;
	int	ceiling_color;

	floor_color = create_trgb(0, data->floor.r, data->floor.g, data->floor.b);
	ceiling_color = create_trgb(0, data->ceiling.r, 
			data->ceiling.g, data->ceiling.b);
	
	y = 0;
	while (y < WIN_HEIGHT / 2)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			put_pixel_to_img(&data->img, x, y, ceiling_color);
			x++;
		}
		y++;
	}
	
	y = WIN_HEIGHT / 2;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			put_pixel_to_img(&data->img, x, y, floor_color);
			x++;
		}
		y++;
	}
}

void	raycast(t_data *data)
{
	int	x;
    
	draw_floor_ceiling(data);
	x = 0;
	while (x < WIN_WIDTH)
	{
		cast_single_ray(data, x);
		x++;
	}
}
