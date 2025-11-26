#ifndef PARSING_H
# define PARSING_H

# include "cub3d.h"

/* ========================================
   PARSING FUNCTION PROTOTYPES
   ======================================== */

// Main parser (parser.c)
int		parse_cub_file(char *filename, t_data *data);

// Parser utilities (parser_utils.c)
char	*get_next_line(int fd);
char	*ft_strtrim(char *str);
int		ft_isspace(char c);
char	**ft_split(char *str, char delimiter);

// Config parsing (parser_config.c)
int		parse_texture(char *line, t_textures *textures);
int		parse_color(char *line, t_color *floor, t_color *ceiling);

// Map parsing (parser_map.c)
int		parse_map(int fd, t_data *data);
void	init_player_direction(t_player *player, char direction);

// Validation (parser_validate.c)
int		validate_textures(t_textures *textures);
int		validate_colors(t_color *floor, t_color *ceiling);
int		validate_map(t_map *map, t_player *player);

#endif
