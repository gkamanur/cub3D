#!/bin/bash
# Create simple 8x8 XPM textures (MiniLibX can scale them)

# Red texture (North)
cat > north.xpm << 'EOF'
/* XPM */
static char *north[] = {
"8 8 2 1",
"  c #FF0000",
". c #AA0000",
"........",
"        ",
"........",
"        ",
"........",
"        ",
"........",
"        "
};
EOF

# Green texture (South)
cat > south.xpm << 'EOF'
/* XPM */
static char *south[] = {
"8 8 2 1",
"  c #00FF00",
". c #00AA00",
"........",
"        ",
"........",
"        ",
"........",
"        ",
"........",
"        "
};
EOF

# Blue texture (West)
cat > west.xpm << 'EOF'
/* XPM */
static char *west[] = {
"8 8 2 1",
"  c #0000FF",
". c #0000AA",
"........",
"        ",
"........",
"        ",
"........",
"        ",
"........",
"        "
};
EOF

# Yellow texture (East)
cat > east.xpm << 'EOF'
/* XPM */
static char *east[] = {
"8 8 2 1",
"  c #FFFF00",
". c #AAAA00",
"........",
"        ",
"........",
"        ",
"........",
"        ",
"........",
"        "
};
EOF

echo "Textures created"
