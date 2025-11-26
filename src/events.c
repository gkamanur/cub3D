#include "../includes/cub3d.h"
#include "../includes/rendering.h"

/**
 * Handle key press events
 * Returns: 0 (required by MiniLibX)
 */
int	handle_keypress(int keycode, t_data *data)
{
	printf("Key pressed: %d\n", keycode);

	if (keycode == KEY_ESC)
	{
		printf("ESC pressed - Closing...\n");
		destroy_window(data);
		exit(0);
	}
	else if (keycode == KEY_W)
		move_forward(data);
	else if (keycode == KEY_S)
		move_backward(data);
	else if (keycode == KEY_A)
		strafe_left(data);
	else if (keycode == KEY_D)
		strafe_right(data);
	else if (keycode == KEY_LEFT)
		rotate_left(data);
	else if (keycode == KEY_RIGHT)
		rotate_right(data);

	return (0);
}

/**
 * Handle window close event (red X button)
 * Returns: 0 (required by MiniLibX)
 */
int	handle_close(t_data *data)
{
	printf("Window close button clicked\n");
	destroy_window(data);
	exit(0);
	return (0);
}

/**
 * Register all event hooks
 */
void	setup_hooks(t_data *data)
{
	// Hook for key press events
	mlx_hook(data->win_ptr, EVENT_KEY_PRESS, 1L<<0, handle_keypress, data);
	
	// Hook for window close (red X)
	mlx_hook(data->win_ptr, EVENT_DESTROY, 0, handle_close, data);
	
	printf("✓ Event hooks registered\n");
}
