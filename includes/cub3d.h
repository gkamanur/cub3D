#ifndef CUB3D_H
# define CUB3D_H

# include "../minilibx-linux/mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <math.h>
# include <stdbool.h>

/* ========================================
   DEFINES
   ======================================== */

// Window settings
# define WIN_WIDTH 3840
# define WIN_HEIGHT 2160
# define WIN_TITLE "Cub3D"

// Key codes (Linux)
# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363

// Event codes
# define EVENT_KEY_PRESS 2
# define EVENT_KEY_RELEASE 3
# define EVENT_DESTROY 17

/* ========================================
   STRUCTURES
   ======================================== */

// Image buffer for fast rendering
typedef struct s_img
{
	void	*img_ptr;		// Image pointer
	char	*addr;			// Image data address
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;			// Texture width
	int		height;			// Texture height
}	t_img;

// Texture paths
typedef struct s_textures
{
	char	*north;
	char	*south;
	char	*west;
	char	*east;
	t_img	north_img;
	t_img	south_img;
	t_img	west_img;
	t_img	east_img;
}	t_textures;

// RGB color
typedef struct s_color
{
	int		r;
	int		g;
	int		b;
}	t_color;

// Player data
typedef struct s_player
{
	double	x;			// Position X
	double	y;			// Position Y
	double	dir_x;		// Direction vector X
	double	dir_y;		// Direction vector Y
	double	plane_x;	// Camera plane X
	double	plane_y;	// Camera plane Y
}	t_player;

// Map data
typedef struct s_map
{
	char	**grid;		// 2D array
	int		width;
	int		height;
}	t_map;

// Main game structure
typedef struct s_data
{
	void		*mlx_ptr;	// MiniLibX connection
	void		*win_ptr;	// Window pointer
	t_img		img;		// Image buffer
	t_textures	textures;	// Wall textures
	t_color		floor;		// Floor color
	t_color		ceiling;	// Ceiling color
	t_map		map;		// Game map
	t_player	player;		// Player info
}	t_data;

/* ========================================
   FUNCTION PROTOTYPES
   ======================================== */

// Window management (window.c)
int		init_window(t_data *data);
void	destroy_window(t_data *data);

// Event handlers (events.c)
int		handle_keypress(int keycode, t_data *data);
int		handle_close(t_data *data);
void	setup_hooks(t_data *data);

// Core utilities (utils.c)
void	print_controls(void);
void	error_exit(char *message);

// Debug utilities (debug.c)
void	draw_background(t_data *data);
void	draw_minimap(t_data *data);
void	debug_print_config(t_data *data);

void	put_pixel_to_img(t_img *img, int x, int y, int color);
int	get_texture_pixel(t_img *texture, int x, int y);

#endif
