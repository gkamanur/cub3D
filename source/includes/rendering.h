/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 16:27:19 by gkamanur          #+#    #+#             */
/*   Updated: 2025/12/12 16:51:04 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

// Debug visualization (debug.c)
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

// Lighting effects (lighting.c)
int		apply_torch_lighting(int color, double distance);
int		apply_floor_ceiling_lighting(t_data *data, int color, int y);

// Performance optimization (performance.c)
void	update_fps(void);
void	limit_framerate(int target_fps);
int		get_raycast_step(void);
void	duplicate_column(t_data *data, int src_x, int count);
void	fast_background_fill(t_data *data, int ceiling_color, int floor_color);
void	enable_vsync(t_data *data);
int		should_use_low_quality(double distance);

// Smooth rendering (smooth_render.c)
void	request_redraw(void);
int		needs_redraw(void);
void	clear_redraw_flag(void);
int		smooth_render_loop(t_data *data);

void	draw_minimap(t_data *data);
