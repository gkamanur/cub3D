/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 16:26:48 by gkamanur          #+#    #+#             */
/*   Updated: 2025/12/19 15:22:40 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include "../includes/parsing.h"
#include "../includes/rendering.h"

/**
 * Main program entry point
 */
void	cleanup_and_exit(t_data *data)
{
	if (data->img.img_ptr)
		mlx_destroy_image(data->mlx_ptr, data->img.img_ptr);
	if (data->win_ptr)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	if (data->mlx_ptr)
	{
		mlx_destroy_display(data->mlx_ptr);  // Add this line
		free(data->mlx_ptr);
	}
	free_data(data);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
	{
		printf("Usage: %s <map.cub>\n", argv[0]);
		return (1);
	}
	printf("Starting Cub3D...\n");
	if (!parse_cub_file(argv[1], &data))
	{
		free_data(&data);
		return (1);
	}
	debug_print_config(&data);
	if (init_window(&data) != 0)
	{
		free_data(&data);
		return (1);
	}
	if (!init_image(&data))
	{
		cleanup_and_exit(&data);
		return (1);
	}
	if (!load_textures(&data))
	{
		cleanup_and_exit(&data);
		return (1);
	}
	print_controls();
	printf("Rendering first frame...\n");
	render_frame(&data);
	printf("✓ Initial render complete\n");
	setup_hooks(&data);
	mlx_loop_hook(data.mlx_ptr, smooth_render_loop, &data);
	printf("Entering main loop...\n");
	mlx_loop(data.mlx_ptr);
	cleanup_and_exit(&data);
	return (0);
}
// int	main(int argc, char **argv)
// {
// 	t_data	data;

// 	if (argc != 2)
// 	{
// 		printf("Usage: %s <map.cub>\n", argv[0]);
// 		return (1);
// 	}
// 	printf("Starting Cub3D...\n");
// 	if (!parse_cub_file(argv[1], &data))
// 	{
//     	free_data(&data);
// 		return (1);
// 	}
// 	// Print parsed config for verification
// 	debug_print_config(&data);
// 	//Initialize window
// 	if (init_window(&data) != 0)
// 		return (1);
// 	// Initialize image buffer
// 	if (!init_image(&data))
// 		return (1);
// 	// Load wall textures
// 	if (!load_textures(&data))
// 		return (1);
// 	// Print controls
// 	print_controls();
// 	// Render initial frame (includes minimap)
// 	printf("Rendering first frame...\n");
// 	render_frame(&data);
// 	printf("✓ Initial render complete\n");
// 	// Setup event handlers
// 	setup_hooks(&data);
// 	// Setup smooth rendering loop
// 	mlx_loop_hook(data.mlx_ptr, smooth_render_loop, &data);
// 	// Start event loop (blocks until window is closed)
// 	printf("Entering main loop...\n");
// 	mlx_loop(data.mlx_ptr);
// 	free_data(&data);
// 	return (0);
// }
