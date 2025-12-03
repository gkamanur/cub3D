#include "../../includes/rendering.h"

// Smooth rendering with frame synchronization
static int g_needs_redraw = 1;  // Start with initial draw needed

// Mark that a redraw is needed (called by movement/events)
void	request_redraw(void)
{
	g_needs_redraw = 1;
}

// Check if redraw is needed
int	needs_redraw(void)
{
	return (g_needs_redraw);
}

// Clear redraw flag (called after rendering)
void	clear_redraw_flag(void)
{
	g_needs_redraw = 0;
}

// Main rendering loop - called continuously, only renders when needed
int	smooth_render_loop(t_data *data)
{
	// Only render if something changed
	if (needs_redraw())
	{
		render_frame(data);
		clear_redraw_flag();
	}
	else
	{
		// If nothing to render, sleep a bit to reduce CPU usage
		usleep(1000);  // 1ms sleep
	}
	
	return (0);
}
