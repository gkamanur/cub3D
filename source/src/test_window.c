
#include "../minilibx-linux/mlx.h"
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    void *mlx_ptr;
    void *win_ptr;
    
    // Initialize minilibx
    mlx_ptr = mlx_init();
    if (!mlx_ptr)
    {
        printf("Error: Failed to initialize MiniLibX\n");
        return (1);
    }
    
    // Create a window (width: 800, height: 600, title: "Cub3D Test")
    win_ptr = mlx_new_window(mlx_ptr, 800, 600, "Cub3D Test");
    if (!win_ptr)
    {
        printf("Error: Failed to create window\n");
        return (1);
    }
    
    printf("Window created successfully! Press any key in the window...\n");
    
    // Keep window open
    mlx_loop(mlx_ptr);
    
    return (0);
}