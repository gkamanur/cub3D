#ifndef RENDERING_H
# define RENDERING_H

# include "cub3d.h"

/* ========================================
   RENDERING FUNCTION PROTOTYPES
   ======================================== */

// Image buffer management (render.c)
int		init_image(t_data *data);
int		load_textures(t_data *data);
void	put_pixel_to_img(t_img *img, int x, int y, int color);
int		get_texture_pixel(t_img *texture, int x, int y);
void	render_frame(t_data *data);
void	draw_minimap(t_data *data);
// Raycasting engine (raycast.c)
void	raycast(t_data *data);

// Movement and controls (movement.c)
void	move_forward(t_data *data);
void	move_backward(t_data *data);
void	strafe_left(t_data *data);
void	strafe_right(t_data *data);
void	rotate_left(t_data *data);
void	rotate_right(t_data *data);

#endif
