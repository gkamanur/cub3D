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

// Draw ceiling and floor colors - OPTIMIZED
static void	render_background(t_data *data)
{
	int			*pixels;
	int			ceiling_color;
	int			floor_color;
	int			total_pixels;
	int			half_pixels;
	int			i;

	ceiling_color = (data->ceiling.r << 16) | (data->ceiling.g << 8) | data->ceiling.b;
	floor_color = (data->floor.r << 16) | (data->floor.g << 8) | data->floor.b;
	
	// Direct memory access - MUCH faster than pixel-by-pixel!
	pixels = (int *)data->img.addr;
	total_pixels = WIN_WIDTH * WIN_HEIGHT;
	half_pixels = total_pixels / 2;
	
	// Optimized fill: 4 pixels at a time when possible
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

// Main render function - called every frame
void	render_frame(t_data *data)
{
	// Draw background (ceiling and floor)
	render_background(data);
	// Perform raycasting to draw walls
	raycast(data);
	// Display the rendered frame
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img_ptr, 0, 0);
}
