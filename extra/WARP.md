# WARP.md

This file provides guidance to WARP (warp.dev) when working with code in this repository.

## Project Overview

cub3D is a raycasting-based 3D game engine (inspired by Wolfenstein 3D) built using C and MiniLibX. It renders first-person perspective graphics by parsing `.cub` map files and rendering textured walls with lighting effects.

## Build System

### Building the Project
```bash
make        # Build the executable
make re     # Rebuild from scratch (fclean + all)
make clean  # Remove object files
make fclean # Remove object files and executable
```

### Running the Program
```bash
make run              # Build and run with default map (maps/map.cub)
./cub3D maps/test.cub # Run with specific map file
```

### Memory Debugging
```bash
make valgrind  # Run with valgrind memory leak detection on default map
valgrind --leak-check=full --show-leak-kinds=all ./cub3D maps/test.cub
```

### Makefile Debug Info
```bash
make debug  # Print Makefile variables and configuration
```

## Architecture

### Module Structure

The codebase is organized into three primary modules:

#### 1. Parsing Module (`source/src/parsing/`)
Handles `.cub` file parsing and validation:
- **parse/**: Core parsing logic for config and map data
  - `parser_cub.c` - Main entry point for parsing `.cub` files
  - `parse_config.c` - Parses texture paths and color definitions
- **colors_xpn/**: Texture and color parsing/validation
  - `parse_rgb.c` - RGB color parsing (e.g., `F 139,69,23`)
  - `parse_textures.c` - XPM texture path extraction
  - `xpm_file_check.c` - Validates XPM file accessibility
- **map/**: Map grid allocation and processing
  - `alloc_free_grid.c` - Dynamic allocation for rectangular map grid
  - `pad_and_copy.c` - Pads irregular maps with spaces to create rectangular grid
- **validation/**: Map integrity checks
  - `parser_validate.c` - Orchestrates all validation steps
  - `borders.c` - Ensures map is fully enclosed by walls
  - `valid_player.c` - Validates exactly one player spawn position (N/S/E/W)
  - `rows.c`, `column.c` - Validates row/column boundaries
- **initialization/**: Game state initialization
  - `init_data.c` - Initializes main `t_data` structure
  - `init_player.c` - Sets player position and direction vectors based on spawn character
- **utils/**: Helper functions
  - `gnl.c` - Custom get_next_line implementation with configurable `BUFFER_SIZE`
  - `parser_utils.c` - String trimming and map line detection

#### 2. Rendering Module (`source/src/rendering/`)
Implements raycasting engine and visual effects:
- `raycast.c` - DDA raycasting algorithm; casts rays for each vertical screen column to determine wall distances and texture coordinates
- `render.c` - Image buffer management, texture loading (MiniLibX), and frame rendering orchestration
- `movement.c` - Player movement (forward/backward/strafe) and rotation with collision detection
- `lighting.c` - Torch mode lighting effects based on wall distance
- `minimap.c` - Top-down 2D minimap overlay
- `performance.c` - Adaptive quality system with column duplication for performance optimization
- `smooth_render.c` - Frame rate management and render loop

#### 3. Events Module (`source/src/events/`)
Handles window and input events:
- `window.c` - MiniLibX window initialization and cleanup
- `events.c` - Keyboard event handlers (WASD movement, arrow key rotation, ESC to exit)
- `utils.c` - Control instruction printing and error handling
- `debug.c` - Debug visualization (config printing, color/texture info)

### Data Flow

1. **Initialization**: `main.c` → `parse_cub_file()` → validates config + map → initializes `t_data`
2. **Window Setup**: `init_window()` creates MiniLibX window and image buffer
3. **Texture Loading**: `load_textures()` loads 4 directional wall textures as `t_img` structures
4. **Event Loop**: MiniLibX event loop processes input → updates player position/direction → triggers redraw
5. **Rendering**: `render_frame()` → `raycast()` → draws textured walls + floor/ceiling + optional minimap

### Key Data Structures

- **`t_data`**: Main game state container (window, textures, map, player, colors)
- **`t_player`**: Position (x, y), direction vector (dir_x, dir_y), camera plane (plane_x, plane_y)
- **`t_map`**: 2D grid of chars ('0'=floor, '1'=wall, ' '=void, 'N/S/E/W'=player spawn)
- **`t_textures`**: Paths + loaded `t_img` structures for north/south/east/west walls
- **`t_color`**: RGB triplet for floor/ceiling

### Map File Format (`.cub`)

Example from `maps/test.cub`:
```
NO ./textures/matrix.xpm    # North wall texture
SO ./textures/matrix.xpm    # South wall texture
WE ./textures/ganesh.xpm    # West wall texture
EA ./textures/matrix.xpm    # East wall texture

F 139,69,23                 # Floor RGB color
C 000,63,200                # Ceiling RGB color

        1111111111111111111111111
        11000000000110000000000001
        1011000001110000000000001
        ...
        11110111 1110101  101111010001  # Spaces are valid
        11111111 1111111  11111111111
```

**Validation Requirements**:
- Map must be fully enclosed by walls (`1`)
- Exactly one player spawn point (`N`, `S`, `E`, or `W`)
- Only valid characters: `0` (walkable), `1` (wall), ` ` (void), `N/S/E/W` (player)
- Irregular maps are automatically padded to rectangular grid
- No empty rows/columns that would disconnect map sections

## Dependencies

- **MiniLibX** (`minilibx-linux/`): X11-based graphics library for Linux
  - Provides window management, image rendering, and event handling
  - Built automatically by Makefile
- **libft** (`libft/`): Custom C standard library implementation (42 project requirement)
  - String manipulation, memory management, etc.
  - Built as static library (`libft.a`)

## Controls (Runtime)

- **WASD**: Move forward/left/backward/right
- **Left/Right Arrow**: Rotate camera
- **T**: Toggle torch lighting mode
- **L**: Toggle texture mode (textures vs solid colors)
- **ESC**: Exit program

## Development Guidelines

### Adding New Features

1. **New rendering effects**: Add functions to `rendering/` module; update `render_frame()` in `render.c`
2. **New map validation**: Add validator to `parsing/validation/`; call from `validate_map()` in `parser_validate.c`
3. **New input handling**: Add key codes to `cub3d.h` (`KEY_*`); implement handler in `events/events.c`

### Code Style

- Follow 42 School norminette style (functions ≤25 lines, ≤5 functions per file, tab indentation)
- Header guards: `#ifndef MODULE_H` pattern
- All headers in `source/includes/`; organized by module (`cub3d.h`, `parsing.h`, `rendering.h`)

### Memory Management

- All heap allocations must have corresponding `free()` calls
- Use `free_data()` from `parsing/map/free_data.c` to clean up main structure
- Texture images must be destroyed with `mlx_destroy_image()` before `mlx_destroy_window()`

### Debugging

- Use `make valgrind` to detect memory leaks
- Enable debug prints: call `debug_print_config()` in `main.c` (currently commented out)
- Visual debugging: minimap renders automatically when `draw_minimap()` is called in render loop

## Common Issues

### Linking Errors
- Ensure MiniLibX and libft are built before main compilation: `make -C minilibx-linux && make -C libft`
- MiniLibX requires X11 development libraries: `sudo apt-get install libx11-dev libxext-dev`

### Map Parsing Failures
- Verify `.cub` file format matches specification (see "Map File Format" section)
- Check file permissions and paths for texture files
- Use `debug_print_config()` to inspect parsed data

### Performance Issues
- Adjust `get_raycast_step()` in `performance.c` to control column duplication
- Reduce `WIN_WIDTH` and `WIN_HEIGHT` in `cub3d.h` for lower resolution
