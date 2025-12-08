NAME = cub3D

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

# Directories
SRC_DIR = source/src
OBJ_DIR = obj
INC_DIR = source/includes
MLX_DIR = minilibx-linux

# MiniLibX
MLX_LIB = $(MLX_DIR)/libmlx.a
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

# Source files
# Core
SRC = $(SRC_DIR)/main.c \
	  $(SRC_DIR)/window.c \
	  $(SRC_DIR)/events.c \
	  $(SRC_DIR)/utils.c \
	  $(SRC_DIR)/debug.c

# Parsing module
SRC += $(SRC_DIR)/parsing/parser.c \
	   $(SRC_DIR)/parsing/parser_utils.c \
	   $(SRC_DIR)/parsing/parser_config.c \
	   $(SRC_DIR)/parsing/parser_map.c \
	   $(SRC_DIR)/parsing/parser_validate.c

# Rendering module
SRC += $(SRC_DIR)/rendering/render.c \
	   $(SRC_DIR)/rendering/raycast.c \
	   $(SRC_DIR)/rendering/lighting.c \
	   $(SRC_DIR)/rendering/performance.c \
	   $(SRC_DIR)/rendering/smooth_render.c \
	   $(SRC_DIR)/rendering/movement.c \
	   $(SRC_DIR)/rendering/minimap.c

# Object files (in obj/ directory)
OBJ = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))

# Colors for output
GREEN = \033[0;32m
YELLOW = \033[0;33m
RED = \033[0;31m
BLUE = \033[0;34m
NC = \033[0m # No Color

all: $(MLX_LIB) $(NAME)

$(MLX_LIB):
	@echo "$(YELLOW)Compiling MiniLibX...$(NC)"
	@make -C $(MLX_DIR) > /dev/null 2>&1
	@echo "$(GREEN)✓ MiniLibX compiled$(NC)"

# Create obj directory and subdirectories if they don't exist
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)/parsing
	@mkdir -p $(OBJ_DIR)/rendering
	@echo "$(BLUE)✓ Created $(OBJ_DIR) directory structure$(NC)"

$(NAME): $(OBJ_DIR) $(OBJ)
	@echo "$(YELLOW)Linking $(NAME)...$(NC)"
	@$(CC) $(OBJ) $(MLX_FLAGS) -o $(NAME)
	@echo "$(GREEN)✓ $(NAME) created successfully!$(NC)"

# Compilation rule: src/file.c -> obj/file.o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@echo "$(YELLOW)Compiling $<...$(NC)"
	@$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

clean:
	@echo "$(RED)Cleaning object files...$(NC)"
	@rm -rf $(OBJ_DIR)
	@make -C $(MLX_DIR) clean > /dev/null 2>&1
	@echo "$(GREEN)✓ Clean done$(NC)"

fclean: clean
	@echo "$(RED)Removing $(NAME)...$(NC)"
	@rm -f $(NAME)
	@echo "$(GREEN)✓ Full clean done$(NC)"

re: fclean all

run: all
	@echo "$(GREEN)Running $(NAME)...$(NC)"
	@./$(NAME)

# Debug: show variables
debug:
	@echo "$(BLUE)===== Makefile Debug Info =====$(NC)"
	@echo "$(YELLOW)NAME:$(NC) $(NAME)"
	@echo "$(YELLOW)SRC_DIR:$(NC) $(SRC_DIR)"
	@echo "$(YELLOW)OBJ_DIR:$(NC) $(OBJ_DIR)"
	@echo "$(YELLOW)Sources:$(NC)"
	@echo "$(SRC)" | tr ' ' '\n'
	@echo "$(YELLOW)Objects:$(NC)"
	@echo "$(OBJ)" | tr ' ' '\n'

.PHONY: all clean fclean re run debug
