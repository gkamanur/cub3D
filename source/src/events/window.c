#include "../../includes/cub3d.h"

int	init_window(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
	{
		error_exit("Failed to initialize MiniLibX");
		return (1);
	}
	data->win_ptr = mlx_new_window(data->mlx_ptr, WIN_WIDTH, WIN_HEIGHT,
			WIN_TITLE);
	if (!data->win_ptr)
	{
		error_exit("Failed to create window");
		return (1);
	}
	printf("✓ Window created successfully (%dx%d)\n", WIN_WIDTH, WIN_HEIGHT);
	return (0);
}

void	destroy_window(t_data *data)
{
	if (data->win_ptr)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		data->win_ptr = NULL;
	}
	printf("✓ Window destroyed\n");
}
