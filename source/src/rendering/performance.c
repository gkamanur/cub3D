#include "../../includes/rendering.h"
#include <sys/time.h>

// FPS counter and frame timing
static double	g_last_frame_time = 0;
static int		g_frame_count = 0;
static double	g_fps = 0;

// Get current time in seconds
static double	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec + tv.tv_usec / 1000000.0);
}

// Update FPS counter
void	update_fps(void)
{
	double	current_time;
	static double	fps_timer = 0;

	current_time = get_time();
	g_frame_count++;
	
	// Update FPS every second
	if (current_time - fps_timer >= 1.0)
	{
		g_fps = g_frame_count / (current_time - fps_timer);
		g_frame_count = 0;
		fps_timer = current_time;
		printf("FPS: %.1f\n", g_fps);
	}
}

// Frame limiter - prevents tearing and reduces CPU usage
void	limit_framerate(int target_fps)
{
	double	current_time;
	double	target_frame_time;
	double	sleep_time;

	current_time = get_time();
	target_frame_time = 1.0 / target_fps;
	
	if (g_last_frame_time > 0)
	{
		sleep_time = target_frame_time - (current_time - g_last_frame_time);
		if (sleep_time > 0)
			usleep((int)(sleep_time * 1000000));
	}
	
	g_last_frame_time = get_time();
}

// Adaptive quality based on resolution
int	get_raycast_step(void)
{
	// For 4K (3840x2160) - cast every 2nd or 3rd ray
	if (WIN_WIDTH >= 3000)
		return (3);  // Cast every 3rd ray at 4K
	else if (WIN_WIDTH >= 2000)
		return (2);  // Cast every 2nd ray at 1440p+
	else if (WIN_WIDTH >= 1600)
		return (2);  // Cast every 2nd ray at high res
	else
		return (1);  // Full quality at 1080p and below
}

// Optimized column duplication for raycast step > 1
void	duplicate_column(t_data *data, int src_x, int count)
{
	int		y;
	int		dup;
	char	*src_col;
	char	*dst_col;
	int		bytes_per_pixel;
	int		*src_pixel;
	int		*dst_pixel;

	bytes_per_pixel = data->img.bits_per_pixel / 8;
	
	// Use direct 32-bit copy for speed
	for (dup = 1; dup < count && (src_x + dup) < WIN_WIDTH; dup++)
	{
		src_col = data->img.addr + (src_x * bytes_per_pixel);
		dst_col = data->img.addr + ((src_x + dup) * bytes_per_pixel);
		
		// Copy entire column using 32-bit operations
		for (y = 0; y < WIN_HEIGHT; y++)
		{
			src_pixel = (int *)(src_col + y * data->img.line_length);
			dst_pixel = (int *)(dst_col + y * data->img.line_length);
			*dst_pixel = *src_pixel;
		}
	}
}

// Memory-efficient background fill (optimized for large resolutions)
void	fast_background_fill(t_data *data, int ceiling_color, int floor_color)
{
	int		*pixels;
	int		half_screen;
	int		i;
	int		batch_size;

	pixels = (int *)data->img.addr;
	half_screen = (WIN_WIDTH * WIN_HEIGHT) / 2;
	batch_size = 8;  // Process 8 pixels at once
	
	// Fill ceiling (top half) - unrolled loop
	i = 0;
	while (i < half_screen - batch_size)
	{
		pixels[i] = ceiling_color;
		pixels[i + 1] = ceiling_color;
		pixels[i + 2] = ceiling_color;
		pixels[i + 3] = ceiling_color;
		pixels[i + 4] = ceiling_color;
		pixels[i + 5] = ceiling_color;
		pixels[i + 6] = ceiling_color;
		pixels[i + 7] = ceiling_color;
		i += batch_size;
	}
	while (i < half_screen)
		pixels[i++] = ceiling_color;
	
	// Fill floor (bottom half) - unrolled loop
	while (i < (WIN_WIDTH * WIN_HEIGHT) - batch_size)
	{
		pixels[i] = floor_color;
		pixels[i + 1] = floor_color;
		pixels[i + 2] = floor_color;
		pixels[i + 3] = floor_color;
		pixels[i + 4] = floor_color;
		pixels[i + 5] = floor_color;
		pixels[i + 6] = floor_color;
		pixels[i + 7] = floor_color;
		i += batch_size;
	}
	while (i < (WIN_WIDTH * WIN_HEIGHT))
		pixels[i++] = floor_color;
}

// Vertical sync hint (if MLX supports it)
void	enable_vsync(t_data *data)
{
	// Most modern MLX implementations handle this automatically
	// but we can add hints for X11
	(void)data;
	// This is a placeholder - MLX may not expose this directly
}

// Reduce texture sampling quality for distant walls (optional)
int	should_use_low_quality(double distance)
{
	// Use lower quality textures for walls very far away
	if (WIN_WIDTH >= 3000 && distance > 10.0)
		return (1);
	else if (WIN_WIDTH >= 2000 && distance > 15.0)
		return (1);
	return (0);
}
