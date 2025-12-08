#include "../../includes/cub3d.h"
#include "../../includes/rendering.h"

static int	handle_escape(int keycode, t_data *data)
{
	if (keycode == KEY_ESC)
	{
		printf("ESC pressed - Closing...\n");
		destroy_window(data);
		exit(0);
	}
	return (0);
}

static int	handle_movement_keys(int keycode, t_data *data)
{
	if (keycode == KEY_W)
		move_forward(data);
	else if (keycode == KEY_S)
		move_backward(data);
	else if (keycode == KEY_A)
		strafe_left(data);
	else if (keycode == KEY_D)
		strafe_right(data);
	else
		return (0);
	return (1);
}

static int	handle_rotation_keys(int keycode, t_data *data)
{
	if (keycode == KEY_LEFT)
		rotate_left(data);
	else if (keycode == KEY_RIGHT)
		rotate_right(data);
	else
		return (0);
	return (1);
}

static int	handle_toggle_keys(int keycode, t_data *data)
{
	if (keycode == KEY_T)
	{
		data->texture_mode = !data->texture_mode;
		printf("Switched to %s mode\n",
			data->texture_mode ? "TEXTURE" : "COLOR");
		request_redraw();
		return (1);
	}
	if (keycode == KEY_L)
	{
		data->torch_mode = !data->torch_mode;
		printf("Torch mode %s\n", data->torch_mode ? "ENABLED" : "DISABLED");
		request_redraw();
		return (1);
	}
	return (0);
}

int	handle_keypress(int keycode, t_data *data)
{
	if (handle_escape(keycode, data))
		return (0);
	if (handle_movement_keys(keycode, data))
		return (0);
	if (handle_rotation_keys(keycode, data))
		return (0);
	if (handle_toggle_keys(keycode, data))
		return (0);
	return (0);
}

int	handle_close(t_data *data)
{
	printf("Window close button clicked\n");
	destroy_window(data);
	exit(0);
	return (0);
}

void	setup_hooks(t_data *data)
{
	mlx_hook(data->win_ptr, EVENT_KEY_PRESS, 1L << 0, handle_keypress, data);
	mlx_hook(data->win_ptr, EVENT_DESTROY, 0, handle_close, data);
	printf("✓ Event hooks registered\n");
}
