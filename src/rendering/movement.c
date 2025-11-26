#include "../../includes/rendering.h"

#define MOVE_SPEED 0.08
#define ROT_SPEED 0.05

// Check if position is valid (not a wall)
static int	is_valid_position(t_data *data, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)x;
	map_y = (int)y;
	// Check bounds
	if (map_x < 0 || map_x >= data->map.width ||
		map_y < 0 || map_y >= data->map.height)
		return (0);
	// Check if position is wall
	if (data->map.grid[map_y][map_x] == '1')
		return (0);
	return (1);
}

// Move forward (W key)
void	move_forward(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->player.x + data->player.dir_x * MOVE_SPEED;
	new_y = data->player.y + data->player.dir_y * MOVE_SPEED;
	// Check collision separately for x and y to allow sliding along walls
	if (is_valid_position(data, new_x, data->player.y))
		data->player.x = new_x;
	if (is_valid_position(data, data->player.x, new_y))
		data->player.y = new_y;
	// Re-render frame
	render_frame(data);
}

// Move backward (S key)
void	move_backward(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->player.x - data->player.dir_x * MOVE_SPEED;
	new_y = data->player.y - data->player.dir_y * MOVE_SPEED;
	if (is_valid_position(data, new_x, data->player.y))
		data->player.x = new_x;
	if (is_valid_position(data, data->player.x, new_y))
		data->player.y = new_y;
	render_frame(data);
}

// Strafe left (A key)
void	strafe_left(t_data *data)
{
	double	new_x;
	double	new_y;

	// Perpendicular to direction is (-dir_y, dir_x)
	new_x = data->player.x - data->player.dir_y * MOVE_SPEED;
	new_y = data->player.y + data->player.dir_x * MOVE_SPEED;
	if (is_valid_position(data, new_x, data->player.y))
		data->player.x = new_x;
	if (is_valid_position(data, data->player.x, new_y))
		data->player.y = new_y;
	render_frame(data);
}

// Strafe right (D key)
void	strafe_right(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->player.x + data->player.dir_y * MOVE_SPEED;
	new_y = data->player.y - data->player.dir_x * MOVE_SPEED;
	if (is_valid_position(data, new_x, data->player.y))
		data->player.x = new_x;
	if (is_valid_position(data, data->player.x, new_y))
		data->player.y = new_y;
	render_frame(data);
}

// Rotate left (← key) - counterclockwise
void	rotate_left(t_data *data)
{
	double	old_dir_x;
	double	old_plane_x;
	double	cos_rot;
	double	sin_rot;

	cos_rot = cos(ROT_SPEED);
	sin_rot = sin(ROT_SPEED);
	// Rotate direction vector
	old_dir_x = data->player.dir_x;
	data->player.dir_x = data->player.dir_x * cos_rot - data->player.dir_y * sin_rot;
	data->player.dir_y = old_dir_x * sin_rot + data->player.dir_y * cos_rot;
	// Rotate camera plane vector
	old_plane_x = data->player.plane_x;
	data->player.plane_x = data->player.plane_x * cos_rot - data->player.plane_y * sin_rot;
	data->player.plane_y = old_plane_x * sin_rot + data->player.plane_y * cos_rot;
	render_frame(data);
}

// Rotate right (→ key) - clockwise
void	rotate_right(t_data *data)
{
	double	old_dir_x;
	double	old_plane_x;
	double	cos_rot;
	double	sin_rot;

	cos_rot = cos(-ROT_SPEED);
	sin_rot = sin(-ROT_SPEED);
	// Rotate direction vector
	old_dir_x = data->player.dir_x;
	data->player.dir_x = data->player.dir_x * cos_rot - data->player.dir_y * sin_rot;
	data->player.dir_y = old_dir_x * sin_rot + data->player.dir_y * cos_rot;
	// Rotate camera plane vector
	old_plane_x = data->player.plane_x;
	data->player.plane_x = data->player.plane_x * cos_rot - data->player.plane_y * sin_rot;
	data->player.plane_y = old_plane_x * sin_rot + data->player.plane_y * cos_rot;
	render_frame(data);
}
