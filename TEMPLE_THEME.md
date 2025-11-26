# 🕉️ Indian Temple Architecture Theme 🏛️

## 🎨 Overview

Your Cub3D game now features authentic Indian temple architecture! Each wall, floor, and ceiling has been carefully designed to evoke the grandeur and intricate beauty of ancient Indian temples.

---

## 🧱 Wall Textures

### **North Wall - Carved Sandstone Pillars** 🏛️
- **Colors:** Sandstone beige (#D4A373) with dark carved details (#8B6F47)
- **Pattern:** Vertical pillars with horizontal decorative carvings
- **Inspiration:** The iconic pillared halls (mandapas) found in South Indian temples like Madurai Meenakshi Temple
- **Features:**
  - Vertical pillar edges every 16 pixels
  - Horizontal carved bands representing decorative moldings
  - Central ornamental lines mimicking floral carvings

### **South Wall - Red Sandstone with Lotus Patterns** 🪷
- **Colors:** Red sandstone (#C1876B) with dark terracotta accents (#8B4513)
- **Pattern:** Repeating lotus flower motifs
- **Inspiration:** The red sandstone walls of North Indian temples (Rajasthan, Agra)
- **Features:**
  - Diamond-shaped lotus patterns
  - Sacred lotus is a recurring motif in Hindu and Buddhist architecture
  - Represents purity, enlightenment, and divine beauty

### **West Wall - Gray Granite with Geometric Mandalas** ⚪
- **Colors:** Gray granite (#A9A9A9) with dark gray details (#696969)
- **Pattern:** Concentric geometric patterns inspired by temple ceiling designs
- **Inspiration:** The intricate ceiling designs of Dilwara Temples and Ranakpur Jain Temple
- **Features:**
  - Concentric squares creating depth
  - Diagonal crossing patterns
  - Mathematical precision reflecting cosmic harmony

### **East Wall - Golden Stone with Deity Niches** ✨
- **Colors:** Golden stone (#DAA520) with dark gold accents (#B8860B)
- **Pattern:** Arched niches for deity sculptures
- **Inspiration:** The gopuram (tower) walls with multiple deity alcoves
- **Features:**
  - Arched openings mimicking temple shrine niches
  - Traditional arch shape used in Indian architecture
  - Represents the sacred spaces housing divine figures

---

## 🎨 Floor & Ceiling Colors

### **Floor - Dark Brown Stone** 🟤
- **Color:** RGB(139, 69, 19) - Saddle Brown
- **Represents:** Polished stone flooring typical of temple interiors
- **Similar to:** Granite, basalt, or polished sandstone floors
- **Feel:** Grounded, ancient, earthy

### **Ceiling - Golden Sandstone** 🟡
- **Color:** RGB(205, 133, 63) - Peru/Golden Brown
- **Represents:** Ornate painted ceilings or golden stone work
- **Similar to:** The warm glow of oil lamps (diyas) on stone ceilings
- **Feel:** Warm, illuminated, divine

---

## 🏛️ Architectural Elements Explained

### **Why These Patterns?**

1. **Pillars (North Wall)**
   - Essential element in temple construction
   - Support massive stone roofs
   - Often carved with deities, dancers, or floral motifs
   - Examples: Hampi, Khajuraho, Ellora Caves

2. **Lotus Motifs (South Wall)**
   - Most sacred flower in Indian culture
   - Symbolizes spiritual awakening
   - Found extensively in temple art
   - Examples: Lotus Temple Delhi, carved lotus ceilings

3. **Geometric Patterns (West Wall)**
   - Represent cosmic order (ऋत - Rita)
   - Mathematical precision in sacred architecture
   - Create meditative focus points
   - Examples: Jain temple ceilings, Islamic-influenced Indo-Saracenic architecture

4. **Deity Niches (East Wall)**
   - House sacred sculptures (murtis)
   - Each deity has designated space
   - Arched alcoves create depth and shadow
   - Examples: Temples of Tamil Nadu, Hoysala temples

---

## 🎨 Color Symbolism

### Temple Stone Colors:
- **Sandstone (Beige/Brown):** Most common building material, represents Earth
- **Red Sandstone:** Prosperity, energy, used in Mughal and Rajput architecture
- **Gray Granite:** Durability, strength, South Indian temple tradition
- **Golden Tones:** Divine light, sacred spaces, represents the sun

### Floor & Ceiling:
- **Dark Brown Floor:** Represents the earthly realm, grounding
- **Golden Ceiling:** Represents the heavens, divine realm

---

## 🕉️ Cultural Context

### Temple Architecture Styles Represented:

1. **Dravidian Style** (South India)
   - Gopuram towers
   - Pillared halls (mandapas)
   - Granite construction
   - Examples: Brihadeeswarar Temple, Shore Temple

2. **Nagara Style** (North India)
   - Curved shikhara towers
   - Sandstone construction
   - Intricate carvings
   - Examples: Khajuraho, Konark Sun Temple

3. **Vesara Style** (Central India)
   - Hybrid of Dravidian and Nagara
   - Star-shaped platforms
   - Detailed sculptures
   - Examples: Hoysala temples, Belur Chennakeshava

---

## 🎮 Experiencing the Temple

### What to Notice While Playing:

1. **Directional Aesthetics**
   - Each cardinal direction has unique stonework
   - North = Structural (pillars)
   - South = Devotional (lotus)
   - West = Cosmic (geometry)
   - East = Sacred (deity spaces)

2. **Color Harmony**
   - Warm earth tones throughout
   - Natural stone colors
   - Golden lighting effect from ceiling
   - Dark grounding from floor

3. **Pattern Recognition**
   - Repetitive motifs (like temple art)
   - Mathematical precision
   - Sacred geometry
   - Symmetry and balance

---

## 🛠️ Technical Implementation

### Texture Files:
```
textures/
├── north.xpm  → Carved pillars pattern (64x64, 2 colors)
├── south.xpm  → Lotus flower pattern (64x64, 2 colors)
├── west.xpm   → Geometric mandala (64x64, 2 colors)
└── east.xpm   → Deity niche arches (64x64, 2 colors)
```

### Map Configuration:
```
F 139,69,19    ← Floor: Dark brown stone
C 205,133,63   ← Ceiling: Golden sandstone
```

### Pattern Algorithms:

**Carved Pillars:**
```python
pillar_x = x % 16  # 16-pixel wide pillars
if pillar_x in [0,1,14,15]: draw_edge()
if y % 8 in [0,1]: draw_horizontal_carving()
```

**Lotus Pattern:**
```python
center_distance = abs(x-8) + abs(y-8)  # Manhattan distance
if center_distance in [6,7]: draw_lotus_outline()
```

**Geometric Mandala:**
```python
min_distance = min(x, y, 31-x, 31-y)  # Distance from edges
if min_distance in [0,8,15]: draw_square()
```

**Deity Niches:**
```python
arch_distance = abs(x - center)
if arch_distance >= (10 - y): draw_arch()
```

---

## 🎨 Customization Ideas

### Create Your Own Temple Style:

1. **Color Variations:**
   ```
   # White marble (like Taj Mahal)
   base_color = '#F5F5F5'
   accent_color = '#DCDCDC'
   
   # Black granite (like Tirupati temple)
   base_color = '#2F4F4F'
   accent_color = '#000000'
   
   # Pink sandstone (Jaipur/Rajasthan)
   base_color = '#FFB6C1'
   accent_color = '#FF69B4'
   ```

2. **Additional Patterns:**
   - Peacock motifs (vahana of Goddess Saraswati)
   - Om symbols
   - Swastika patterns (ancient symbol of prosperity)
   - Kalasha (sacred pot) designs
   - Dancing figures (like Nataraja)

3. **Floor/Ceiling Combinations:**
   ```
   # Marble temple
   F 240,240,240  (White marble floor)
   C 255,215,0    (Gold leaf ceiling)
   
   # Stone temple
   F 105,105,105  (Dark gray granite)
   C 160,82,45    (Sienna ceiling)
   ```

---

## 📚 Historical References

### Famous Indian Temples for Inspiration:

1. **Brihadeeswarar Temple, Tamil Nadu** (1010 CE)
   - Massive granite construction
   - Intricate carvings
   - Tall vimana (tower)

2. **Khajuraho Temples, Madhya Pradesh** (950-1050 CE)
   - Nagara style architecture
   - Sandstone construction
   - Detailed sculptures

3. **Dilwara Temples, Rajasthan** (11th-13th century)
   - White marble
   - Incredible ceiling work
   - Jain temple architecture

4. **Meenakshi Temple, Madurai** (12th century onwards)
   - Colorful gopurams
   - Thousand pillar hall
   - Dravidian architecture

5. **Hoysala Temples, Karnataka** (12th-13th century)
   - Star-shaped platforms
   - Soapstone carvings
   - Lathe-turned pillars

---

## 🕉️ Sacred Symbolism in the Game

### The Four Directions (Dikpāla):

In Hindu cosmology, each direction is guarded by a deity:

- **East (Pūrva):** Indra - King of Gods → Golden deity niches
- **South (Dakṣiṇa):** Yama - God of Death → Red lotus (rebirth)
- **West (Paścima):** Varuṇa - God of Water → Geometric (cosmic ocean)
- **North (Uttara):** Kubera - God of Wealth → Stone pillars (stability)

### Playing as Spiritual Journey:

- **Floor (Earth):** Material world
- **Walls (Temples):** Path of dharma
- **Ceiling (Sky):** Ultimate liberation (moksha)
- **Navigation:** Life's journey through sacred spaces

---

## 🎉 Final Touches

### Enhance Your Temple Experience:

1. **Lighting:** The golden ceiling creates warm ambient lighting
2. **Shadows:** Pattern depth creates texture and realism
3. **Immersion:** Close your eyes and imagine oil lamps flickering
4. **Sound:** (Future) Add temple bells, chanting, or flute music

---

## 🙏 Credits and Respect

This theme is created with deep respect for Indian architectural heritage and spiritual traditions. The patterns are simplified interpretations meant to evoke the grandeur of temple architecture while working within the technical constraints of the raycasting engine.

> "Architecture is the built testament of devotion, where stone becomes spirit."
> — Traditional temple architecture philosophy

---

## 🔄 Switching Between Themes

To go back to modern/brick style, regenerate textures using the texture creation script in the extras folder.

To modify the temple theme:
```bash
# Edit the Python script
nano create_temple_textures.py

# Run it
python3 create_temple_textures.py

# Rebuild and run
make re
./cub3D maps/test.cub
```

---

**Now walk through your sacred temple maze! Each turn reveals new architectural wonders.** 🕉️✨

*Namaste* 🙏
