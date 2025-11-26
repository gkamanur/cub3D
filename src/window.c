#include "../includes/cub3d.h"

/**
 * Initialize MiniLibX and create window
 * Returns: 0 on success, 1 on failure
 */
int	init_window(t_data *data)
{
	// Initialize MiniLibX
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
	{
		error_exit("Failed to initialize MiniLibX");
		return (1);
	}

	// Create window
	data->win_ptr = mlx_new_window(data->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, WIN_TITLE);
	if (!data->win_ptr)
	{
		error_exit("Failed to create window");
		return (1);
	}

	printf("✓ Window created successfully (%dx%d)\n", WIN_WIDTH, WIN_HEIGHT);
	return (0);
}

/**
 * Clean up and destroy window
 */
void	destroy_window(t_data *data)
{
	if (data->win_ptr)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		data->win_ptr = NULL;
	}
	// Note: We don't destroy mlx_ptr as it causes issues on Linux
	printf("✓ Window destroyed\n");
}
