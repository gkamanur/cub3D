#include "../../includes/cub3d.h"
#include "../../includes/rendering.h"

static void	debug_print_textures(t_textures *tex)
{
	printf("Textures:\n");
	printf("  North:  %s\n", tex->north);
	printf("  South:  %s\n", tex->south);
	printf("  West:   %s\n", tex->west);
	printf("  East:   %s\n", tex->east);
}

static void	debug_print_colors(t_color *floor, t_color *ceiling)
{
	printf("\nColors:\n");
	printf("  Floor:   RGB(%d, %d, %d)\n", floor->r, floor->g, floor->b);
	printf("  Ceiling: RGB(%d, %d, %d)\n", ceiling->r, ceiling->g, ceiling->b);
}

static void	debug_print_map_info(t_map *map)
{
	int	y;

	printf("\nMap:\n");
	printf("  Size:    %d x %d\n", map->width, map->height);
	printf("  Grid:\n");
	y = 0;
	while (y < map->height)
	{
		printf("    [%s]\n", map->grid[y]);
		y++;
	}
}

static void	debug_print_player_info(t_player *player)
{
	printf("\nPlayer:\n");
	printf("  Position:  (%.2f, %.2f)\n", player->x, player->y);
	printf("  Direction: (%.2f, %.2f)\n", player->dir_x, player->dir_y);
	printf("  Plane:     (%.2f, %.2f)\n", player->plane_x, player->plane_y);
}

void	debug_print_config(t_data *data)
{
	printf("\n========== PARSED CONFIGURATION ==========\n");
	debug_print_textures(&data->textures);
	debug_print_colors(&data->floor, &data->ceiling);
	debug_print_map_info(&data->map);
	debug_print_player_info(&data->player);
	printf("==========================================\n\n");
}
