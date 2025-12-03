#include "../includes/cub3d.h"
#include "../includes/rendering.h"


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
