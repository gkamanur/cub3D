#include "../../includes/rendering.h"

// DDA raycasting for one vertical slice
static void	cast_ray(t_data *data, int x)
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;

	// Calculate ray position and direction
	camera_x = 2 * x / (double)WIN_WIDTH - 1; // x-coordinate in camera space
	ray_dir_x = data->player.dir_x + data->player.plane_x * camera_x;
	ray_dir_y = data->player.dir_y + data->player.plane_y * camera_x;
	
	// Which box of the map we're in
	map_x = (int)data->player.x;
	map_y = (int)data->player.y;
	
	// Length of ray from one x or y-side to next x or y-side
	delta_dist_x = (ray_dir_x == 0) ? 1e30 : fabs(1 / ray_dir_x);
	delta_dist_y = (ray_dir_y == 0) ? 1e30 : fabs(1 / ray_dir_y);
	
	// Calculate step and initial sideDist
	if (ray_dir_x < 0)
	{
		step_x = -1;
		side_dist_x = (data->player.x - map_x) * delta_dist_x;
	}
	else
	{
		step_x = 1;
		side_dist_x = (map_x + 1.0 - data->player.x) * delta_dist_x;
	}
	if (ray_dir_y < 0)
	{
		step_y = -1;
		side_dist_y = (data->player.y - map_y) * delta_dist_y;
	}
	else
	{
		step_y = 1;
		side_dist_y = (map_y + 1.0 - data->player.y) * delta_dist_y;
	}
	
	// Perform DDA
	hit = 0;
	while (hit == 0)
	{
		// Jump to next map square, either in x-direction, or in y-direction
		if (side_dist_x < side_dist_y)
		{
			side_dist_x += delta_dist_x;
			map_x += step_x;
			side = 0; // x-side hit
		}
		else
		{
			side_dist_y += delta_dist_y;
			map_y += step_y;
			side = 1; // y-side hit
		}
		// Check if ray has hit a wall
		if (map_x < 0 || map_x >= data->map.width || 
			map_y < 0 || map_y >= data->map.height ||
			data->map.grid[map_y][map_x] == '1')
			hit = 1;
	}
	
	// Calculate distance projected on camera direction (Euclidean distance gives fisheye effect!)
	if (side == 0)
		perp_wall_dist = (map_x - data->player.x + (1 - step_x) / 2) / ray_dir_x;
	else
		perp_wall_dist = (map_y - data->player.y + (1 - step_y) / 2) / ray_dir_y;
	
	// Calculate height of line to draw on screen
	int	line_height = (int)(WIN_HEIGHT / perp_wall_dist);
	
	// Calculate lowest and highest pixel to fill in current stripe
	int	draw_start = -line_height / 2 + WIN_HEIGHT / 2;
	if (draw_start < 0)
		draw_start = 0;
	int	draw_end = line_height / 2 + WIN_HEIGHT / 2;
	if (draw_end >= WIN_HEIGHT)
		draw_end = WIN_HEIGHT - 1;
	
	// Calculate wall x coordinate (where exactly the wall was hit)
	double	wall_x;
	if (side == 0)
		wall_x = data->player.y + perp_wall_dist * ray_dir_y;
	else
		wall_x = data->player.x + perp_wall_dist * ray_dir_x;
	wall_x -= floor(wall_x);
	
	// Choose texture based on wall direction
	t_img	*texture;
	if (side == 0)
	{
		if (ray_dir_x > 0)
			texture = &data->textures.west_img;  // West side
		else
			texture = &data->textures.east_img;  // East side
	}
	else
	{
		if (ray_dir_y > 0)
			texture = &data->textures.north_img; // North side
		else
			texture = &data->textures.south_img; // South side
	}
	
	// x coordinate on the texture (using actual texture width)
	int	tex_x = (int)(wall_x * (double)texture->width);
	if ((side == 0 && ray_dir_x > 0) || (side == 1 && ray_dir_y < 0))
		tex_x = texture->width - tex_x - 1;
	// Clamp tex_x to valid range
	if (tex_x < 0)
		tex_x = 0;
	else if (tex_x >= texture->width)
		tex_x = texture->width - 1;
	
	// How much to increase the texture coordinate per screen pixel
	double	step = (double)texture->height / line_height;
	// Starting texture coordinate
	double	tex_pos = (draw_start - WIN_HEIGHT / 2 + line_height / 2) * step;
	
	// Draw the textured vertical line
	int	y = draw_start;
	while (y < draw_end)
	{
		int tex_y = (int)tex_pos;
		if (tex_y < 0)
			tex_y = 0;
		else if (tex_y >= texture->height)
			tex_y = texture->height - 1;
		tex_pos += step;
		int color = get_texture_pixel(texture, tex_x, tex_y);
		// Apply torch lighting if enabled
		if (data->torch_mode)
			color = apply_torch_lighting(color, perp_wall_dist);
		put_pixel_to_img(&data->img, x, y, color);
		y++;
	}
}

// Main raycasting function - casts rays for all screen columns
void	raycast(t_data *data)
{
	int		x;
	int		step;
	int		bytes_per_pixel;

	// Use adaptive quality system
	step = get_raycast_step();

	bytes_per_pixel = data->img.bits_per_pixel / 8;
	x = 0;
	while (x < WIN_WIDTH)
	{
		cast_ray(data, x);
		
		// Fast column duplication using direct memory copy
		if (step > 1)
		{
			int dup;
			for (dup = 1; dup < step && (x + dup) < WIN_WIDTH; dup++)
			{
				int y;
				char *src_col = data->img.addr + (x * bytes_per_pixel);
				char *dst_col = data->img.addr + ((x + dup) * bytes_per_pixel);
				
				// Copy entire column at once (much faster!)
				for (y = 0; y < WIN_HEIGHT; y++)
				{
					*(unsigned int *)(dst_col + y * data->img.line_length) = 
					*(unsigned int *)(src_col + y * data->img.line_length);
				}
			}
		}
		x += step;
	}
}
