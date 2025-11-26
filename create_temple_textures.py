#!/usr/bin/env python3
"""
Indian Temple Architecture Texture Generator for Cub3D
Creates XPM texture files with traditional Indian temple patterns
"""

def create_temple_wall(filename, base_color, accent_color, pattern_type):
    """
    Create temple-style wall textures with different patterns
    
    Args:
        filename: Output XPM file path
        base_color: Main stone/wall color (hex format, e.g., '#D4A373')
        accent_color: Carved details/decorations (hex format)
        pattern_type: Type of architectural pattern to generate
    """
    with open(filename, 'w') as f:
        f.write('/* XPM */\n')
        f.write('static char *texture[] = {\n')
        f.write('"64 64 2 1",\n')
        f.write(f'"  c {base_color}",\n')
        f.write(f'". c {accent_color}",\n')
        
        for y in range(64):
            row = ''
            for x in range(64):
                pixel = ' '  # default to base color
                
                if pattern_type == 'carved_pillars':
                    # Vertical pillars with horizontal carvings
                    pillar_x = x % 16
                    if pillar_x == 0 or pillar_x == 1 or pillar_x == 14 or pillar_x == 15:
                        pixel = '.'  # pillar edges
                    elif y % 8 == 0 or y % 8 == 1:
                        pixel = '.'  # horizontal carvings
                    elif pillar_x == 7 or pillar_x == 8:
                        if y % 4 == 0:
                            pixel = '.'  # center decorative line
                
                elif pattern_type == 'lotus_pattern':
                    # Repeating lotus/flower motifs
                    block_x = x % 16
                    block_y = y % 16
                    # Create diamond/lotus shape
                    center_dist = abs(block_x - 8) + abs(block_y - 8)
                    if center_dist == 6 or center_dist == 7:
                        pixel = '.'
                    elif block_y == 0 or block_y == 15:
                        if block_x % 4 == 0:
                            pixel = '.'
                
                elif pattern_type == 'geometric_mandala':
                    # Geometric patterns inspired by temple ceiling designs
                    block_x = x % 32
                    block_y = y % 32
                    # Create concentric squares
                    min_dist = min(block_x, block_y, 31-block_x, 31-block_y)
                    if min_dist == 0 or min_dist == 8 or min_dist == 15:
                        pixel = '.'
                    elif (block_x + block_y) % 8 == 0:
                        pixel = '.'
                
                elif pattern_type == 'deity_niches':
                    # Arched niches like those housing deity sculptures
                    niche_x = x % 20
                    niche_y = y % 20
                    # Create arch shape
                    if niche_y < 3 or niche_y > 17:
                        if niche_x == 0 or niche_x == 19:
                            pixel = '.'
                    elif niche_y < 10:
                        # Arch top
                        arch_dist = abs(niche_x - 10)
                        if arch_dist >= 10 - niche_y:
                            pixel = '.'
                    else:
                        # Niche sides
                        if niche_x == 0 or niche_x == 19:
                            pixel = '.'
                
                row += pixel
            
            if y < 63:
                f.write(f'"{row}",\n')
            else:
                f.write(f'"{row}"\n')
        
        f.write('};\n')

def main():
    """Generate all four temple wall textures"""
    
    print("🕉️  Generating Indian Temple Architecture Textures...")
    print()
    
    # North wall - Sandstone with carved pillars
    create_temple_wall(
        'textures/north.xpm',
        '#D4A373',  # Sandstone beige
        '#8B6F47',  # Dark carved details
        'carved_pillars'
    )
    print("✓ North wall: Sandstone with carved pillars")
    
    # South wall - Red sandstone with lotus patterns
    create_temple_wall(
        'textures/south.xpm',
        '#C1876B',  # Red sandstone
        '#8B4513',  # Dark terracotta
        'lotus_pattern'
    )
    print("✓ South wall: Red sandstone with lotus patterns")
    
    # West wall - Gray granite with geometric mandalas
    create_temple_wall(
        'textures/west.xpm',
        '#A9A9A9',  # Gray granite
        '#696969',  # Dark gray details
        'geometric_mandala'
    )
    print("✓ West wall: Gray granite with geometric mandalas")
    
    # East wall - Golden stone with deity niches
    create_temple_wall(
        'textures/east.xpm',
        '#DAA520',  # Golden stone
        '#B8860B',  # Dark gold
        'deity_niches'
    )
    print("✓ East wall: Golden stone with deity niches")
    
    print()
    print("🏛️  All temple textures created successfully!")
    print()
    print("Recommended map colors:")
    print("  Floor (F):   139,69,19   (Dark brown stone)")
    print("  Ceiling (C): 205,133,63  (Golden sandstone)")
    print()
    print("Now run: ./cub3D maps/test.cub")

if __name__ == '__main__':
    main()
