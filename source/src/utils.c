#include "../includes/cub3d.h"

/**
 * Print controls information
 */
void	print_controls(void)
{
	printf("\n");
	printf("╔════════════════════════════════════╗\n");
	printf("║         CUB3D CONTROLS             ║\n");
	printf("╠════════════════════════════════════╣\n");
	printf("║  ESC         - Exit program        ║\n");
	printf("║  W           - Move forward        ║\n");
	printf("║  S           - Move backward       ║\n");
	printf("║  A           - Strafe left         ║\n");
	printf("║  D           - Strafe right        ║\n");
	printf("║  ← / →       - Rotate view         ║\n");
	printf("║  T           - Toggle texture mode ║\n");
	printf("║  L           - Toggle torch mode     ║\n");
	printf("║  Red X       - Close window        ║\n");
	printf("╚════════════════════════════════════╝\n");
	printf("\n");
}

/**
 * Print error message and exit
 */
void	error_exit(char *message)
{
	printf("Error: %s\n", message);
	exit(1);
}
