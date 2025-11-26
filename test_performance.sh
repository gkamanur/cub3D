#!/bin/bash
# Quick performance test for different resolutions

echo "🎮 Cub3D Performance Test"
echo "=========================="
echo ""

# Backup current resolution
cp includes/cub3d.h includes/cub3d.h.backup

# Test function
test_resolution() {
    local width=$1
    local height=$2
    echo "Testing ${width}×${height}..."
    
    # Update resolution
    sed -i "s/# define WIN_WIDTH .*/# define WIN_WIDTH $width/" includes/cub3d.h
    sed -i "s/# define WIN_HEIGHT .*/# define WIN_HEIGHT $height/" includes/cub3d.h
    
    # Rebuild
    make re > /dev/null 2>&1
    
    if [ $? -eq 0 ]; then
        echo "  ✓ Build successful"
        echo "  Run: ./cub3D maps/test.cub"
        echo ""
    else
        echo "  ✗ Build failed"
    fi
}

# Show current optimizations
echo "Current optimizations:"
echo "  - Compiler: -O3 -march=native"
echo "  - Background: 4-pixel unrolled loop"
echo "  - Raycasting: Adaptive (step=3 at 2000+px)"
echo ""

# Test your resolution
test_resolution 2000 2200

echo "To revert to original resolution:"
echo "  mv includes/cub3d.h.backup includes/cub3d.h"
echo "  make re"
