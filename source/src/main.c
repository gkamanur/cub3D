/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 16:26:48 by gkamanur          #+#    #+#             */
/*   Updated: 2025/12/12 14:35:55 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include "../includes/parsing.h"
#include "../includes/rendering.h"

/**
 * Main program entry point
 */
int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
	{
		printf("Usage: %s <map.cub>\n", argv[0]);
		return (1);
	}
	printf("Starting Cub3D...\n");
	// Parse .cub file
	if (!parse_cub_file(argv[1], &data))
		return (1);
	// Print parsed config for verification
	debug_print_config(&data);
	//Initialize window
	if (init_window(&data) != 0)
		return (1);
	// Initialize image buffer
	if (!init_image(&data))
		return (1);
	// Load wall textures
	if (!load_textures(&data))
		return (1);
	// Print controls
	print_controls();
	// Render initial frame (includes minimap)
	printf("Rendering first frame...\n");
	render_frame(&data);
	printf("✓ Initial render complete\n");
	// Setup event handlers
	setup_hooks(&data);
	// Setup smooth rendering loop
	mlx_loop_hook(data.mlx_ptr, smooth_render_loop, &data);
	// Start event loop (blocks until window is closed)
	printf("Entering main loop...\n");
	mlx_loop(data.mlx_ptr);
	return (0);
}
