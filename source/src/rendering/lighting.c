#include "../../includes/rendering.h"

// Apply distance-based lighting (torch effect)
// Returns darkened color based on distance
int	apply_torch_lighting(int color, double distance)
{
	int		r;
	int		g;
	int		b;
	double	brightness;
	double	max_distance;

	// Maximum visible distance with torch (adjust for effect intensity)
	max_distance = 15.0;
	
	// Calculate brightness falloff (inverse square law for realism)
	if (distance > max_distance)
		brightness = 0.0;
	else
		brightness = 1.0 - (distance / max_distance);
	
	// Apply quadratic falloff for more dramatic effect
	brightness = brightness * brightness;
	
	// Ensure minimum brightness so it's not completely dark
	if (brightness < 0.1)
		brightness = 0.1;
	
	// Extract RGB components
	r = (color >> 16) & 0xFF;
	g = (color >> 8) & 0xFF;
	b = color & 0xFF;
	
	// Apply brightness
	r = (int)(r * brightness);
	g = (int)(g * brightness);
	b = (int)(b * brightness);
	
	// Clamp values
	if (r > 255) r = 255;
	if (g > 255) g = 255;
	if (b > 255) b = 255;
	if (r < 0) r = 0;
	if (g < 0) g = 0;
	if (b < 0) b = 0;
	
	// Recombine into color
	return ((r << 16) | (g << 8) | b);
}

// Apply fog effect for floor/ceiling based on distance from center
int	apply_floor_ceiling_lighting(t_data *data, int color, int y)
{
	double	distance_from_center;
	double	brightness;
	int		r;
	int		g;
	int		b;
	
	if (!data->torch_mode)
		return (color);
	
	// Calculate vertical distance from horizon (center of screen)
	distance_from_center = abs(y - WIN_HEIGHT / 2);
	
	// Map distance to brightness (farther = darker)
	brightness = 1.0 - (distance_from_center / (WIN_HEIGHT / 2.0));
	
	// Apply some minimum brightness
	if (brightness < 0.2)
		brightness = 0.2;
	
	// Extract and apply
	r = ((color >> 16) & 0xFF) * brightness;
	g = ((color >> 8) & 0xFF) * brightness;
	b = (color & 0xFF) * brightness;
	
	// Clamp
	if (r > 255) r = 255;
	if (g > 255) g = 255;
	if (b > 255) b = 255;
	
	return ((r << 16) | (g << 8) | b);
}
