#include "../includes/cub3d.h"

// Helper: put pixel directly to window (using mlx_pixel_put is slow but ok for debug)
static void	put_pixel(t_data *data, int x, int y, int color)
{
	if (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT)
		mlx_pixel_put(data->mlx_ptr, data->win_ptr, x, y, color);
}

// Draw ceiling and floor with parsed colors
void	draw_background(t_data *data)
{
	int	x;
	int	y;
	int	ceiling_color;
	int	floor_color;

	// Convert RGB to int color (0xRRGGBB)
	ceiling_color = (data->ceiling.r << 16) | (data->ceiling.g << 8) | data->ceiling.b;
	floor_color = (data->floor.r << 16) | (data->floor.g << 8) | data->floor.b;

	// Draw ceiling (top half)
	y = 0;
	while (y < WIN_HEIGHT / 2)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			put_pixel(data, x, y, ceiling_color);
			x++;
		}
		y++;
	}
	// Draw floor (bottom half)
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			put_pixel(data, x, y, floor_color);
			x++;
		}
		y++;
	}
}

// Draw a simple minimap to visualize the parsed map
void	draw_minimap(t_data *data)
{
	int	scale;
	int	map_x;
	int	map_y;
	int	screen_x;
	int	screen_y;
	int	color;

	scale = 10; // Each map cell is 10x10 pixels
	map_y = 0;
	while (map_y < data->map.height)
	{
		map_x = 0;
		while (map_x < data->map.width)
		{
			// Determine color based on cell type
			if (data->map.grid[map_y][map_x] == '1')
				color = 0xFFFFFF; // White for walls
			else if (data->map.grid[map_y][map_x] == '0')
				color = 0x555555; // Gray for floor
			else
				color = 0x000000; // Black for space
			// Draw cell
			screen_y = 0;
			while (screen_y < scale)
			{
				screen_x = 0;
				while (screen_x < scale)
				{
					put_pixel(data, map_x * scale + screen_x, 
							 map_y * scale + screen_y, color);
					screen_x++;
				}
				screen_y++;
			}
			map_x++;
		}
		map_y++;
	}
	// Draw player position (red dot)
	screen_x = (int)(data->player.x * scale);
	screen_y = (int)(data->player.y * scale);
	int dot_size = 3;
	int dy = -dot_size;
	while (dy <= dot_size)
	{
		int dx = -dot_size;
		while (dx <= dot_size)
		{
			put_pixel(data, screen_x + dx, screen_y + dy, 0xFF0000);
			dx++;
		}
		dy++;
	}
}

// Print parsed configuration to console for verification
void	debug_print_config(t_data *data)
{
	printf("\n========== PARSED CONFIGURATION ==========\n");
	printf("Textures:\n");
	printf("  North:  %s\n", data->textures.north);
	printf("  South:  %s\n", data->textures.south);
	printf("  West:   %s\n", data->textures.west);
	printf("  East:   %s\n", data->textures.east);
	printf("\nColors:\n");
	printf("  Floor:   RGB(%d, %d, %d)\n", 
		   data->floor.r, data->floor.g, data->floor.b);
	printf("  Ceiling: RGB(%d, %d, %d)\n", 
		   data->ceiling.r, data->ceiling.g, data->ceiling.b);
	printf("\nMap:\n");
	printf("  Size:    %d x %d\n", data->map.width, data->map.height);
	printf("  Grid:\n");
	int y = 0;
	while (y < data->map.height)
	{
		printf("    [%s]\n", data->map.grid[y]);
		y++;
	}
	printf("\nPlayer:\n");
	printf("  Position:  (%.2f, %.2f)\n", data->player.x, data->player.y);
	printf("  Direction: (%.2f, %.2f)\n", data->player.dir_x, data->player.dir_y);
	printf("  Plane:     (%.2f, %.2f)\n", data->player.plane_x, data->player.plane_y);
	printf("==========================================\n\n");
}
