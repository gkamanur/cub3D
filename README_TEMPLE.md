# 🕉️ Cub3D - Indian Temple Edition

## Welcome to Your Virtual Temple! 🏛️

This is a **3D raycasting game** with authentic **Indian temple architecture** themes. Walk through ancient temple corridors featuring sandstone pillars, lotus carvings, geometric mandalas, and deity niches!

---

## 🎮 Quick Start

```bash
# Run the game
./cub3D maps/test.cub

# Build from source
make

# Clean and rebuild
make re
```

### Controls:
- **W/S** - Move forward/backward
- **A/D** - Strafe left/right  
- **←/→** - Rotate view
- **ESC** - Exit

---

## 📚 Documentation

We have **three comprehensive guides** for different audiences:

### 1. 📖 **KIDS_GUIDE.md** - For Everyone! 
*Perfect for ages 10+ or anyone new to game development*

- Explains 3D raycasting like magic tricks
- Uses simple analogies (laser pointers, flipbooks)
- No scary math - just fun concepts!
- Great for learning how games work

### 2. 🕉️ **TEMPLE_THEME.md** - Detailed Architecture Guide
*For those interested in Indian culture and architecture*

- Deep dive into each wall pattern
- Cultural and historical context
- Symbolism and meaning
- Famous temple references
- Customization ideas

### 3. 📋 **TEMPLE_QUICK_REFERENCE.md** - Cheat Sheet
*For quick lookups and modifications*

- Color codes at a glance
- Pattern visualizations
- Alternative color schemes
- Quick start commands
- Technical specifications

---

## 🎨 The Temple Theme

Your maze features **four unique walls**:

| Direction | Style | Colors | Pattern |
|-----------|-------|--------|---------|
| 🏛️ **North** | Sandstone Pillars | Beige/Brown | Carved mandapa columns |
| 🪷 **South** | Red Sandstone | Red/Terracotta | Sacred lotus motifs |
| ⚪ **West** | Gray Granite | Gray/Dark Gray | Geometric mandalas |
| ✨ **East** | Golden Stone | Gold/Dark Gold | Deity shrine niches |

**Floor:** Dark brown polished stone (139,69,19)  
**Ceiling:** Golden sandstone glow (205,133,63)

---

## 🛠️ Project Structure

```
cub3d/
├── cub3D                          ← Executable game
├── Makefile                       ← Build instructions
│
├── 📚 Documentation
│   ├── README_TEMPLE.md           ← You are here!
│   ├── KIDS_GUIDE.md              ← Beginner-friendly guide
│   ├── TEMPLE_THEME.md            ← Detailed architecture docs
│   └── TEMPLE_QUICK_REFERENCE.md  ← Quick reference
│
├── 📦 includes/                   ← Header files
│   ├── cub3d.h                    ← Main definitions
│   ├── parsing.h                  ← Map parsing
│   └── rendering.h                ← Graphics rendering
│
├── 💻 src/                        ← Source code
│   ├── main.c
│   ├── window.c
│   ├── events.c
│   ├── parsing/                   ← Map file parsing
│   │   ├── parser.c
│   │   ├── parser_config.c
│   │   ├── parser_map.c
│   │   ├── parser_validate.c
│   │   └── parser_utils.c
│   └── rendering/                 ← 3D raycasting engine
│       ├── render.c
│       ├── raycast.c
│       └── movement.c
│
├── 🎨 textures/                   ← Wall textures (XPM format)
│   ├── north.xpm                  ← Sandstone pillars
│   ├── south.xpm                  ← Lotus patterns
│   ├── west.xpm                   ← Geometric mandalas
│   └── east.xpm                   ← Deity niches
│
├── 🗺️ maps/                       ← Level files
│   └── test.cub                   ← Sample temple maze
│
├── 🔧 Tools
│   └── create_temple_textures.py  ← Texture generator script
│
└── 🛠️ minilibx-linux/             ← Graphics library
```

---

## 🎯 Features

### ✅ Implemented:
- ✨ Real-time 3D raycasting engine
- 🎨 Authentic temple-themed textures
- 🎮 Smooth player movement and rotation
- 🗺️ Map parsing with validation
- 🖼️ Textured walls with proper perspective
- 🌈 Custom floor/ceiling colors
- ⌨️ Keyboard controls (WASD + arrows)
- 🪟 Clean window management

### 🔮 Potential Enhancements:
- 🔊 Sound effects (temple bells, chants)
- 💡 Dynamic lighting (oil lamps)
- 🎭 Animated sprites (deities, devotees)
- 🌊 Reflective floors
- 🌟 Particle effects (incense smoke)
- 📊 Minimap display
- 🎵 Background music (flute, veena)

---

## 🎨 Customization

### Change Wall Textures:
```bash
# Edit the texture generator
nano create_temple_textures.py

# Modify colors and patterns
# Then regenerate:
./create_temple_textures.py

# Rebuild
make re
```

### Change Floor/Ceiling Colors:
```bash
# Edit your map file
nano maps/test.cub

# Change these lines:
F 139,69,19    # Floor RGB
C 205,133,63   # Ceiling RGB
```

### Create New Maps:
```
NO ./textures/north.xpm
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/east.xpm

F 139,69,19
C 205,133,63

111111
100001
10N001
111111
```

---

## 🧮 Technical Details

### Raycasting Algorithm:
1. For each vertical screen column (x = 0 to 799):
   - Calculate ray direction
   - Step through map using DDA algorithm
   - Find wall intersection
   - Calculate wall height based on distance
   - Draw textured wall slice

### Performance:
- **Resolution:** 800×600 pixels
- **Rays per frame:** 800 (one per column)
- **Target FPS:** 60
- **Texture size:** 64×64 per wall

### Graphics Library:
- **MiniLibX** - Lightweight X11 wrapper
- Direct pixel manipulation for speed
- XPM image format for textures

---

## 🏛️ Cultural Respect

This theme is created with **deep respect** for Indian architectural heritage. The patterns are simplified artistic interpretations inspired by:

- 🕉️ Hindu temple architecture (Dravidian, Nagara, Vesara styles)
- 🙏 Jain temple designs (geometric precision)
- 🕌 Indo-Saracenic influences (arch forms)
- 📿 Buddhist motifs (lotus symbolism)

Famous temples referenced:
- **Meenakshi Temple** (Tamil Nadu)
- **Khajuraho** (Madhya Pradesh)
- **Dilwara Temples** (Rajasthan)
- **Brihadeeswarar Temple** (Tamil Nadu)
- **Hoysala Temples** (Karnataka)

---

## 🐛 Troubleshooting

### Texture loading errors?
- Check paths in `.cub` file start with `./`
- Ensure XPM files are in `textures/` directory
- Run texture generator if files are missing

### Map validation errors?
- Ensure map is surrounded by walls (`1`)
- Must have exactly one player (`N`, `S`, `E`, or `W`)
- All texture paths must be valid

### Compilation issues?
```bash
# Clean and rebuild MiniLibX
cd minilibx-linux
make clean
make
cd ..

# Clean and rebuild project
make fclean
make
```

---

## 📜 License & Credits

**Project:** Cub3D (42 School project adapted)  
**Theme:** Indian Temple Architecture  
**Graphics:** MiniLibX library  
**Textures:** Procedurally generated Python script  

Made with ❤️ and respect for ancient wisdom and modern technology.

---

## 🎓 Learning Resources

Want to learn more? Check out:

1. **Raycasting:** Lode's Computer Graphics Tutorial
2. **Temple Architecture:** "Indian Temple Architecture" by Percy Brown
3. **Game Development:** "Game Programming Patterns" by Robert Nystrom
4. **Graphics Programming:** "Computer Graphics: Principles and Practice"

---

## 🙏 Final Words

> "Temple architecture represents the unity of art, mathematics, spirituality, and engineering."

Walk through these virtual temple halls and appreciate the intersection of ancient architectural wisdom and modern computer graphics!

**Namaste** 🙏✨

---

## Quick Commands Cheatsheet

```bash
# Build and run
make && ./cub3D maps/test.cub

# Regenerate temple textures
./create_temple_textures.py

# Full rebuild
make re

# Clean up
make fclean

# Debug mode
make && gdb ./cub3D
```

**Enjoy your temple journey!** 🕉️🏛️
