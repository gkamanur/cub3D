#include "../includes/cub3d.h"
#include "../includes/rendering.h"

/**
 * Handle key press events
 * Returns: 0 (required by MiniLibX)
 */
int	handle_keypress(int keycode, t_data *data)
{
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
	else if (keycode == KEY_T)
	{
		data->texture_mode = !data->texture_mode;
		if (data->texture_mode)
			printf("Switched to TEXTURE mode\n");
		else
			printf("Switched to COLOR mode\n");
		request_redraw();
	}
	else if (keycode == KEY_L)
	{
		data->torch_mode = !data->torch_mode;
		if (data->torch_mode)
			printf("Torch mode ENABLED\n");
		else
			printf("Torch mode DISABLED\n");
		request_redraw();
	}

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
