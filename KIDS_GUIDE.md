# 🎮 Cub3D - A Super Cool 3D Maze Game! 🏰

## 📖 What is This?

Imagine you're inside a video game like the old **Wolfenstein 3D** or **Doom**! This project creates a 3D world that you can walk around in, but it's actually all drawn on a flat 2D screen. Pretty cool magic trick, right? 🪄

Think of it like this: When you look at a photograph of a hallway, it **looks** 3D even though the photo is flat. That's what this program does - it creates pictures that **look** 3D!

---

## 🎨 How Does It Work? The Magic Behind The Scenes

### 1. **The Map (Like a Board Game) 🗺️**

First, we have a map file (like `test.cub`) that describes our maze. It's like drawing a map on graph paper:

```
1 1 1 1 1 1 1
1 0 0 0 0 0 1
1 0 1 1 0 0 1
1 0 0 0 0 N 1
1 1 1 1 1 1 1
```

- `1` = Wall (you can't walk through walls!)
- `0` = Empty space (you can walk here)
- `N` = Player starting position, facing North

### 2. **Raycasting (The Magic Vision) 👁️**

This is the **coolest** part! Imagine you're standing in a dark room with a laser pointer:

1. You shine the laser straight ahead → it hits a wall
2. You measure how far away that wall is
3. **If the wall is close**, you draw it BIG on the screen
4. **If the wall is far away**, you draw it small

Now imagine doing this **800 times** across your screen, super fast! Each laser beam is called a "ray". That's why it's called "ray-casting" - you're casting rays of light!

```
        Wall
         ||
   ray3  || ray4  ray5
      \  ||  /
       \ || /
    ray2\||/ray6
        \|/
   ray1--👤--ray7    ← This is YOU!
        /|\
    ray0/ | \ray8
```

Each ray tells you: "There's a wall this far away!" And then you draw that wall piece.

### 3. **Textures (Wall Decorations) 🧱**

Walls would be boring if they were just one color! So we use **textures** - these are like wallpapers for your walls. We have four different textures:

- 🔴 **North walls** - Red bricks
- 🟢 **South walls** - Green bricks  
- 🔵 **West walls** - Blue bricks
- 🟡 **East walls** - Yellow bricks

These are stored in special `.xpm` files, which are like tiny pictures made of colored squares.

---

## 📁 Project Organization (How Everything is Stored)

Think of this project like a big toolbox with different drawers:

```
cub3d/
├── 📋 Makefile              ← Instructions to build the game
├── 🎮 cub3D                 ← The game (after you build it)
│
├── 📦 includes/             ← "Rule books" (header files)
│   ├── cub3d.h             ← Main rules
│   ├── parsing.h           ← Rules for reading the map
│   └── rendering.h         ← Rules for drawing
│
├── 🗺️ maps/                 ← Your maze designs
│   └── test.cub            ← A sample maze
│
├── 🎨 textures/             ← Wall pictures
│   ├── north.xpm           ← Red brick wall
│   ├── south.xpm           ← Green brick wall
│   ├── west.xpm            ← Blue brick wall
│   └── east.xpm            ← Yellow brick wall
│
├── 💻 src/                  ← The actual code!
│   ├── main.c              ← Where the game starts
│   ├── window.c            ← Creates the game window
│   ├── events.c            ← Handles keyboard presses
│   ├── utils.c             ← Helper tools
│   ├── debug.c             ← Tools to check if things work
│   │
│   ├── 📖 parsing/          ← Reads and checks the map
│   │   ├── parser.c
│   │   ├── parser_config.c
│   │   ├── parser_map.c
│   │   ├── parser_validate.c
│   │   └── parser_utils.c
│   │
│   └── 🎨 rendering/        ← Draws the 3D world
│       ├── render.c        ← Main drawing code
│       ├── raycast.c       ← The magic raycasting!
│       └── movement.c      ← Moving the player
│
└── 🛠️ minilibx-linux/       ← Graphics library (helps draw on screen)
```

---

## 🔧 The Different Parts (Modules)

### Module 1: **Parsing** (Reading the Instructions) 📖

**Files:** `src/parsing/*.c`

This part reads your map file and checks if it makes sense:

- ✅ Does the map have walls all around? (You can't have holes!)
- ✅ Is there exactly one player? (Not zero, not two!)
- ✅ Are the texture files there?
- ✅ Are the colors valid?

It's like a teacher checking your homework!

**Example from the code:**
```c
// Check if map borders are all walls
if (grid[0][x] != '1' && grid[0][x] != ' ')
    return (0);  // Uh oh! No wall at the top!
```

### Module 2: **Rendering** (Drawing the World) 🎨

**Files:** `src/rendering/*.c`

This is where the magic happens!

#### **a) Raycasting** (`raycast.c`)
For each vertical line on your screen:
1. Calculate the angle of the ray
2. Step through the map until you hit a wall
3. Calculate how tall to draw the wall
4. Pick the right color from the texture

#### **b) Rendering** (`render.c`)
- Creates the image buffer (like a blank canvas)
- Draws the ceiling (orange in our map)
- Draws the floor (red in our map)
- Loads and draws wall textures

#### **c) Movement** (`movement.c`)
When you press keys:
- **W** → Move forward
- **S** → Move backward
- **A** → Slide left
- **D** → Slide right
- **←/→** → Turn left/right

### Module 3: **Window & Events** (The Game Screen) 🖼️

**Files:** `window.c`, `events.c`

- Creates an 800×600 pixel window
- Listens for keyboard presses
- Closes the window when you press ESC or click the X

---

## 🎯 How the Game Loop Works

Think of the game like a flipbook - it draws the same picture over and over, but slightly different each time:

```
1. START
   ↓
2. Wait for you to press a key
   ↓
3. Did you press W? → Move player forward
   Did you press ESC? → Quit game
   ↓
4. DRAW everything again (with new position)
   ↓
5. Go back to step 2 (repeat forever!)
```

This happens **super fast** - many times per second!

---

## 🧮 The Math (Don't Worry, It's Not Scary!)

### **Distance Calculation**

When a ray hits a wall, we calculate how far away it is:

```c
distance = sqrt((wall_x - player_x)² + (wall_y - player_y)²)
```

This is the **Pythagorean theorem** - remember triangles? 📐

### **Wall Height**

The closer the wall, the taller we draw it:

```c
wall_height = (SCREEN_HEIGHT / distance)
```

- Close wall: Small distance → BIG height
- Far wall: Big distance → small height

That's what makes it look 3D! 🤯

---

## 🎮 How to Use This Game

### **Building the Game:**

```bash
make
```

This is like saying "Put all the pieces together!"

### **Running the Game:**

```bash
./cub3D maps/test.cub
```

### **Controls:**

- 🏃 **W** - Walk forward
- 🚶 **S** - Walk backward  
- ⬅️ **A** - Slide left
- ➡️ **D** - Slide right
- 🔄 **Left Arrow** - Turn left
- 🔄 **Right Arrow** - Turn right
- 🚪 **ESC** - Exit game

---

## 🛠️ Important Data Structures (The Recipe Cards)

### **t_player** (The Hero - That's You!)

```c
typedef struct s_player
{
    double x;        // Where you are (left-right)
    double y;        // Where you are (up-down)
    double dir_x;    // Which way you're looking (X)
    double dir_y;    // Which way you're looking (Y)
    double plane_x;  // Camera stuff (makes FOV work)
    double plane_y;  // Camera stuff
} t_player;
```

### **t_map** (The Maze Blueprint)

```c
typedef struct s_map
{
    char **grid;     // The actual maze (2D array of characters)
    int width;       // How wide the maze is
    int height;      // How tall the maze is
} t_map;
```

### **t_textures** (The Wall Decorations)

```c
typedef struct s_textures
{
    char *north;      // Path to north texture file
    char *south;      // Path to south texture file
    char *west;       // Path to west texture file
    char *east;       // Path to east texture file
    t_img north_img;  // The actual loaded image
    t_img south_img;  // (and so on...)
    t_img west_img;
    t_img east_img;
} t_textures;
```

---

## 🐛 Common Problems and Solutions

### Problem 1: "Cannot open texture file"
**What happened?** The game can't find the wall pictures.

**Fix:** Make sure the paths in your `.cub` file are correct:
```
NO ./textures/north.xpm    ← Good! (starts with ./)
NO ../textures/north.xpm   ← Bad! (wrong path)
```

### Problem 2: "Map not surrounded by walls"
**What happened?** There's a hole in your maze!

**Fix:** Make sure your map has `1`s all around the edges:
```
1 1 1 1 1    ← All 1s at top
1 0 0 0 1    ← 1s on sides
1 0 0 0 1    ← 1s on sides
1 1 1 1 1    ← All 1s at bottom
```

### Problem 3: "Failed to load texture"
**What happened?** The XPM file is broken or too complicated.

**Fix:** Use simple XPM files with only 2 colors (like we created).

---

## 🌟 Cool Things to Try

1. **Make Your Own Map!**
   - Open `maps/test.cub`
   - Change the numbers to create your own maze
   - Make it simple first, then more complex!

2. **Change the Colors!**
   - In the `.cub` file, change:
     ```
     F 220,100,0    ← Floor color (Red, Green, Blue)
     C 225,30,0     ← Ceiling color
     ```
   - Try `F 0,0,255` for a blue floor!

3. **Create New Textures!**
   - Draw your own patterns in the `.xpm` files
   - Make rainbow walls!
   - Make stone walls!
   - Make anything you imagine!

---

## 🎓 What You Learn From This Project

1. **Graphics Programming** - How games draw things on screen
2. **Math in Action** - Using angles, distances, and vectors
3. **File Reading** - How programs read configuration files
4. **Problem Solving** - Breaking big problems into small pieces
5. **3D Illusions** - How to fake 3D on a 2D screen

---

## 📚 Fun Facts

🎮 **Did you know?** The first 3D games like Wolfenstein 3D (1992) used this exact technique! Modern games use more advanced methods, but raycasting is where it all started!

🚀 **Speed:** This program can cast 800 rays and draw a full frame 60 times per second - that's 48,000 rays per second!

🧙 **Magic Trick:** Even though you see a 3D world, every wall is actually just a tall rectangle. Your brain fills in the rest!

---

## 🎉 Summary

You've created a **3D game engine** from scratch! Here's what happens:

1. 📖 Read a map file (like reading a recipe)
2. 🎨 Load wall textures (get your ingredients)
3. 👁️ Cast rays in all directions (shine flashlights everywhere)
4. 📏 Calculate distances (measure how far things are)
5. 🖼️ Draw walls based on distance (paint the picture)
6. 🎮 Let the player move around (play the game!)
7. 🔁 Repeat 60 times per second (keep the flipbook going!)

---

## 🤔 Questions for Curious Minds

1. **Why do far away things look smaller?**
   - Because they take up less of your vision! Hold your finger close to your eye, then far away. See?

2. **Why 800 rays across the screen?**
   - Our window is 800 pixels wide, so we need one ray per column!

3. **Could we make it look more realistic?**
   - Yes! We could add:
     - Shadows
     - More detailed textures
     - Lighting effects
     - Objects like tables and chairs
     - Even enemies to chase you!

4. **Is this how modern games work?**
   - Not quite! Modern games use **3D models** and **GPU acceleration**, which is even more complex. But they all started with ideas like this!

---

## 🎨 The Map File Explained (For Future Maze Makers!)

Here's what a complete map file looks like:

```
NO ./textures/north.xpm    ← North wall texture
SO ./textures/south.xpm    ← South wall texture  
WE ./textures/west.xpm     ← West wall texture
EA ./textures/east.xpm     ← East wall texture

F 220,100,0                ← Floor color (RGB)
C 225,30,0                 ← Ceiling color (RGB)

        1111111111
        1000000001         ← Your maze!
        100N000001         ← N = player faces North
        1000000001
        1111111111
```

**Other player directions:**
- `N` = North (up)
- `S` = South (down)
- `W` = West (left)
- `E` = East (right)

---

## 🏆 You Are Now a 3D Graphics Wizard! 🧙‍♂️

You understand how games create the illusion of 3D worlds! Next time you play a game, you'll know the magic happening behind the scenes. Maybe one day, you'll create the next amazing game that millions of people play!

**Remember:** Every expert was once a beginner. Keep learning, keep coding, and most importantly - **have fun!** 🚀✨

---

*Made with ❤️ by someone who thinks coding is like magic!*
