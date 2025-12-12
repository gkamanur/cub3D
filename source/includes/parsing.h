/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 16:27:15 by gkamanur          #+#    #+#             */
/*   Updated: 2025/12/12 16:50:55 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "cub3d.h"

/* ========================================
   PARSING FUNCTION PROTOTYPES
   ======================================== */
typedef struct s_gnl_data
{
	char		buffer[BUFFER_SIZE];
	int			buffer_pos;
	int			buffer_read;
	int			eof;
}				t_gnl_data;

typedef struct s_extent
{
	int			start;
	int			end;
}				t_extent;

typedef struct s_map_extents
{
	t_extent	*rows;
	int			height;
}				t_map_extents;

char			*gnl(int fd);
char			*my_strtrim(char *str);
int				ft_isspace(char c);
int				trim_line(char *line, char **trimmed_out);
int				check_map_empty(t_map *map);
int				is_player_char(char c);

// floor_ceiling
int				extract_rgb(char *src, t_color *dst);
int				handle_floor(char *trimmed, t_color *floor);
int				handle_ceiling(char *trimmed, t_color *ceiling);
int				parse_color(char *line, t_color *floor, t_color *ceiling);
char			**select_cf_destination(char *trimmed, t_textures *textures);
int				parse_cf_texture(char *line, t_textures *textures);

// map
char			**allocate_temp_lines(int size);
void			free_temp_lines(char **lines, int count);
void			init_north(t_player *player);
void			init_south(t_player *player);
void			init_east(t_player *player);
void			init_west(t_player *player);
void			init_player_direction(t_player *player, char direction);
int				is_map_line(char *line);
int				get_max_width(char **lines, int count);
char			*pad_line(char *line, int width);
int				process_first_line(t_data *data, char **temp_lines, int *count);
int				read_map_lines(int fd, char **temp_lines, int *count);
int				pad_and_copy_lines(t_data *data, char **temp_lines, int count);
int				read_and_process_map(int fd, t_data *data, char ***out_lines,
					int *out_count);
int				allocate_grid(t_data *data, char **temp_lines, int count);
int				parse_map(int fd, t_data *data);

// parse

void			init_data(t_data *data);
int				parse_config(int fd, t_data *data, char *line);
int				parse_rgb(char *str, t_color *color);
int				parse_texture(char *line, t_textures *textures);
int				parse_cub_file(char *filename, t_data *data);
int				check_texture_file(char *path, const char *label);
int				check_texture_paths(t_textures *textures);
int				validate_textures(t_textures *textures);
int				validate_colors(t_color *floor, t_color *ceiling);
int				check_borders(char **grid, int width, int height);
void			set_player_position(t_player *player, int x, int y, char c,
					char *dir);
int				scan_map_for_player(t_map *map, t_player *player,
					char *player_dir);
int				find_player(t_map *map, t_player *player, char *player_dir);
int				validate_player_count(int player_count);
int				validate_map(t_map *map, t_player *player);
// borders
void			free_row_extents(t_map_extents *ext);
t_map_extents	compute_row_extents(char **grid, int height);
int				validate_row_border(char *row, t_extent ext, int y);
t_extent		get_row_extent(char *row);
int				get_column_extent(char **grid, int x, int height,
					t_extent *col);
int				check_column_border(char **grid, int x, t_extent col);
int				validate_column(char **grid, int x, int height);
int				check_borders_strict(char **grid, int width, int height);
#endif
