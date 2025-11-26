# 🕉️ Temple Theme - Quick Reference

## 🎨 Color Palette

```
WALLS:
North:  #D4A373 (Sandstone Beige)     + #8B6F47 (Carved Brown)
South:  #C1876B (Red Sandstone)       + #8B4513 (Terracotta)
West:   #A9A9A9 (Gray Granite)        + #696969 (Dark Gray)
East:   #DAA520 (Golden Stone)        + #B8860B (Dark Gold)

FLOOR & CEILING:
Floor:   RGB(139, 69, 19)  - Dark Brown Stone
Ceiling: RGB(205, 133, 63) - Golden Sandstone
```

## 🧱 Wall Patterns

### North - Carved Pillars 🏛️
```
||  ||  ||  ||  ||  ||
==================
||  ||  ||  ||  ||  ||
||  |  ||  |  ||  |  
==================
||  ||  ||  ||  ||  ||
```
**Inspired by:** Mandapa pillared halls

### South - Lotus Motifs 🪷
```
  *   *   *   *
 * * * * * * * *
  * ◊ * * ◊ *
 * * * * * * * *
  *   *   *   *
```
**Inspired by:** Sacred lotus carvings

### West - Geometric Mandala ⚪
```
╔═════════════╗
║ ┌─────────┐ ║
║ │ ┌─────┐ │ ║
║ │ │  +  │ │ ║
║ │ └─────┘ │ ║
║ └─────────┘ ║
╚═════════════╝
```
**Inspired by:** Temple ceiling designs

### East - Deity Niches ✨
```
╭───╮  ╭───╮  ╭───╮
│   │  │   │  │   │
│ ☸ │  │ ☸ │  │ ☸ │
│   │  │   │  │   │
└───┘  └───┘  └───┘
```
**Inspired by:** Gopuram deity alcoves

## 🧭 Directional Symbolism

```
           NORTH (Uttara)
              Kubera
           🏛️ Pillars
               ⬆️
               
WEST        ⬅️  ❖  ➡️      EAST
(Paścima)   Varuṇa 👤 Indra   (Pūrva)
⚪ Mandala         ✨ Niches
               
               ⬇️
          SOUTH (Dakṣiṇa)
               Yama
           🪷 Lotus
```

## 🎮 Controls

```
    ⬆️ W
Move: WASD
Turn: ⬅️ ➡️
Exit: ESC
```

## 🏃 Quick Start

```bash
# Run the game
./cub3D maps/test.cub

# Regenerate textures (if needed)
./create_temple_textures.py

# Rebuild project
make re
```

## 📐 Technical Specs

- **Texture Size:** 64×64 pixels
- **Color Depth:** 2 colors per texture (XPM format)
- **Window:** 800×600 pixels
- **Pattern Repeat:** 16-32 pixels
- **File Format:** XPM (X PixMap)

## 🎨 Alternative Color Schemes

### White Marble Temple
```
F 240,240,240  (White marble floor)
C 255,215,0    (Gold leaf ceiling)

Walls: #F5F5F5 + #DCDCDC
```

### Black Granite Temple
```
F 64,64,64     (Dark granite)
C 139,69,19    (Wooden ceiling)

Walls: #2F4F4F + #000000
```

### Pink Sandstone Temple (Jaipur)
```
F 160,82,45    (Terracotta)
C 255,228,196  (Bisque)

Walls: #FFB6C1 + #FF69B4
```

## 🏛️ Famous Temples Referenced

1. **Meenakshi Temple** - Pillared halls
2. **Khajuraho** - Lotus carvings
3. **Dilwara Temples** - Geometric ceilings
4. **Brihadeeswarar** - Deity niches

## 📝 Files Modified

```
textures/north.xpm  ← New sandstone pillar texture
textures/south.xpm  ← New lotus pattern texture
textures/west.xpm   ← New mandala texture
textures/east.xpm   ← New niche texture
maps/test.cub       ← Updated F/C colors
```

## 🔄 Revert to Original

```bash
# Backup current temple textures
cp textures/*.xpm textures/backup/

# Create simple brick textures (original style)
python3 << 'EOF'
def create_brick(f, c1, c2):
    with open(f, 'w') as file:
        file.write('/* XPM */\nstatic char *t[] = {\n"64 64 2 1",')
        file.write(f'"\\ c {c1}",". c {c2}",')
        for y in range(64):
            r = ''.join('.' if y%8==0 or x%16==0 else ' ' 
                       for x in range(64))
            file.write(f'"{r}"{"," if y<63 else ""}\n')
        file.write('};\n')

create_brick('textures/north.xpm', '#FF0000', '#800000')
create_brick('textures/south.xpm', '#00FF00', '#008000')
create_brick('textures/west.xpm', '#0000FF', '#000080')
create_brick('textures/east.xpm', '#FFFF00', '#808000')
EOF

# Update map colors
# F 220,100,0 (Orange)
# C 225,30,0  (Red-orange)
```

---

**🙏 Namaste - Enjoy your temple journey!** 🕉️
