#include "../../includes/rendering.h"
#include <string.h>

// Initialize image buffer for fast rendering
int	init_image(t_data *data)
{
	data->img.img_ptr = mlx_new_image(data->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	if (!data->img.img_ptr)
	{
		printf("Error\nFailed to create image\n");
		return (0);
	}
	data->img.addr = mlx_get_data_addr(data->img.img_ptr,
										&data->img.bits_per_pixel,
										&data->img.line_length,
										&data->img.endian);
	if (!data->img.addr)
	{
		printf("Error\nFailed to get image data address\n");
		return (0);
	}
	return (1);
}

// Load a single texture from XPM file
static int	load_texture(t_data *data, t_img *tex, char *path)
{
	int	width;
	int	height;

	tex->img_ptr = mlx_xpm_file_to_image(data->mlx_ptr, path, &width, &height);
	if (!tex->img_ptr)
	{
		printf("Error\nFailed to load texture: %s\n", path);
		return (0);
	}
	tex->addr = mlx_get_data_addr(tex->img_ptr, &tex->bits_per_pixel,
								  &tex->line_length, &tex->endian);
	if (!tex->addr)
	{
		printf("Error\nFailed to get texture data\n");
		return (0);
	}
	tex->width = width;
	tex->height = height;
	return (1);
}

// Load all wall textures
int	load_textures(t_data *data)
{
	if (!load_texture(data, &data->textures.north_img, data->textures.north))
		return (0);
	if (!load_texture(data, &data->textures.south_img, data->textures.south))
		return (0);
	if (!load_texture(data, &data->textures.west_img, data->textures.west))
		return (0);
	if (!load_texture(data, &data->textures.east_img, data->textures.east))
		return (0);
	// Load ceiling/floor textures if specified
	if (data->textures.floor_tex)
	{
		if (!load_texture(data, &data->textures.floor_img, data->textures.floor_tex))
			return (0);
		data->use_floor_texture = 1;
		printf("✓ Floor texture loaded\n");
	}
	if (data->textures.ceiling_tex)
	{
		if (!load_texture(data, &data->textures.ceiling_img, data->textures.ceiling_tex))
			return (0);
		data->use_ceiling_texture = 1;
		printf("✓ Ceiling texture loaded\n");
	}
	printf("✓ Textures loaded\n");
	return (1);
}

// Put pixel directly to image buffer (very fast)
void	put_pixel_to_img(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

// Get pixel color from texture
int	get_texture_pixel(t_img *texture, int x, int y)
{
	char	*pixel;

	pixel = texture->addr + (y * texture->line_length + x * (texture->bits_per_pixel / 8));
	return (*(unsigned int *)pixel);
}

// Draw ceiling and floor with colors (optimized)
static void	render_background_color(t_data *data)
{
	int			*pixels;
	int			ceiling_color;
	int			floor_color;
	int			total_pixels;
	int			half_pixels;
	int			i;

	ceiling_color = (data->ceiling.r << 16) | (data->ceiling.g << 8) | data->ceiling.b;
	floor_color = (data->floor.r << 16) | (data->floor.g << 8) | data->floor.b;
	pixels = (int *)data->img.addr;
	total_pixels = WIN_WIDTH * WIN_HEIGHT;
	half_pixels = total_pixels / 2;
	// Fill ceiling (top half)
	i = 0;
	while (i < half_pixels - 4)
	{
		pixels[i] = ceiling_color;
		pixels[i + 1] = ceiling_color;
		pixels[i + 2] = ceiling_color;
		pixels[i + 3] = ceiling_color;
		i += 4;
	}
	while (i < half_pixels)
		pixels[i++] = ceiling_color;
	// Fill floor (bottom half)
	while (i < total_pixels - 4)
	{
		pixels[i] = floor_color;
		pixels[i + 1] = floor_color;
		pixels[i + 2] = floor_color;
		pixels[i + 3] = floor_color;
		i += 4;
	}
	while (i < total_pixels)
		pixels[i++] = floor_color;
}

// Draw ceiling and floor with textures
static void	render_background_texture(t_data *data)
{
	int		x;
	int		y;
	int		tex_x;
	int		tex_y;
	int		color;

	// Render ceiling with texture
	if (data->use_ceiling_texture && data->texture_mode)
	{
		y = 0;
		while (y < WIN_HEIGHT / 2)
		{
			x = 0;
			while (x < WIN_WIDTH)
			{
				tex_x = (x * data->textures.ceiling_img.width) / WIN_WIDTH;
				tex_y = (y * data->textures.ceiling_img.height) / (WIN_HEIGHT / 2);
				color = get_texture_pixel(&data->textures.ceiling_img, tex_x, tex_y);
				color = apply_floor_ceiling_lighting(data, color, y);
				put_pixel_to_img(&data->img, x, y, color);
				x++;
			}
			y++;
		}
	}
	else
	{
		// Use color for ceiling
		int ceiling_color = (data->ceiling.r << 16) | (data->ceiling.g << 8) | data->ceiling.b;
		y = 0;
		while (y < WIN_HEIGHT / 2)
		{
			x = 0;
			while (x < WIN_WIDTH)
				put_pixel_to_img(&data->img, x++, y, apply_floor_ceiling_lighting(data, ceiling_color, y));
			y++;
		}
	}
	// Render floor with texture
	if (data->use_floor_texture && data->texture_mode)
	{
		y = WIN_HEIGHT / 2;
		while (y < WIN_HEIGHT)
		{
			x = 0;
			while (x < WIN_WIDTH)
			{
				tex_x = (x * data->textures.floor_img.width) / WIN_WIDTH;
				tex_y = ((y - WIN_HEIGHT / 2) * data->textures.floor_img.height) / (WIN_HEIGHT / 2);
				color = get_texture_pixel(&data->textures.floor_img, tex_x, tex_y);
				color = apply_floor_ceiling_lighting(data, color, y);
				put_pixel_to_img(&data->img, x, y, color);
				x++;
			}
			y++;
		}
	}
	else
	{
		// Use color for floor
		int floor_color = (data->floor.r << 16) | (data->floor.g << 8) | data->floor.b;
		y = WIN_HEIGHT / 2;
		while (y < WIN_HEIGHT)
		{
			x = 0;
			while (x < WIN_WIDTH)
				put_pixel_to_img(&data->img, x++, y, apply_floor_ceiling_lighting(data, floor_color, y));
			y++;
		}
	}
}

// Draw ceiling and floor - chooses mode based on settings
static void	render_background(t_data *data)
{
	// Use texture mode if textures are available and mode is enabled
	if ((data->use_ceiling_texture || data->use_floor_texture) && data->texture_mode)
		render_background_texture(data);
	else
		render_background_color(data);
}

// Main render function - called every frame
void	render_frame(t_data *data)
{
	// Draw background (ceiling and floor)
	render_background(data);
	// Perform raycasting to draw walls
	raycast(data);
	draw_minimap(data);
	// Draw minimap overlay
	//draw_minimap(data);
	// Display the rendered frame
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img_ptr, 0, 0);
	// Performance tracking and limiting
	update_fps();
}
