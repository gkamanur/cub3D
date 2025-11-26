#!/bin/bash
# High-Quality Photo to Texture Converter for Cub3D

echo "📸 HIGH QUALITY Photo to Texture Converter"
echo "==========================================="
echo ""

# Check if ImageMagick is installed
if ! command -v convert &> /dev/null; then
    echo "❌ ImageMagick not found!"
    echo "Install it with: sudo apt install imagemagick"
    exit 1
fi

# Check if image file is provided
if [ $# -eq 0 ]; then
    echo "Usage: $0 <image.jpg> [output_name]"
    echo ""
    echo "Examples:"
    echo "  $0 photo.jpg              # Creates textures/photo.xpm (256x256 HIGH QUALITY)"
    echo "  $0 wall.jpg north         # Creates textures/north.xpm (256x256)"
    echo ""
    echo "Quality modes:"
    echo "  Default: 256x256 pixels, optimized for clarity"
    echo ""
    exit 1
fi

INPUT_FILE="$1"
OUTPUT_NAME="${2:-$(basename "$INPUT_FILE" | sed 's/\.[^.]*$//')}"

# Check if input file exists
if [ ! -f "$INPUT_FILE" ]; then
    echo "❌ File not found: $INPUT_FILE"
    exit 1
fi

OUTPUT_FILE="textures/${OUTPUT_NAME}.xpm"

echo "🎨 Processing with HIGH QUALITY settings..."
echo "Input:  $INPUT_FILE"
echo "Output: $OUTPUT_FILE"
echo "Size:   256×256 (High Quality)"
echo ""

# Create textures directory if it doesn't exist
mkdir -p textures

# HIGH QUALITY conversion with multiple enhancement steps
echo "⚙️  Step 1: Preprocessing (contrast, sharpness)..."
convert "$INPUT_FILE" \
    -resize 512x512 \
    -auto-level \
    -enhance \
    /tmp/temp_preprocessed.png

echo "⚙️  Step 2: Sharpening and detail enhancement..."
convert /tmp/temp_preprocessed.png \
    -unsharp 2x1+0.5+0 \
    -contrast-stretch 2%x98% \
    /tmp/temp_enhanced.png

echo "⚙️  Step 3: Final resize with best quality algorithm..."
convert /tmp/temp_enhanced.png \
    -filter Lanczos \
    -resize 256x256! \
    -colorspace RGB \
    -colors 256 \
    -depth 8 \
    -define xpm:color-palette=true \
    "$OUTPUT_FILE"

# Clean up temp files
rm -f /tmp/temp_preprocessed.png /tmp/temp_enhanced.png

if [ $? -eq 0 ]; then
    echo ""
    echo "✓ HIGH QUALITY conversion successful!"
    echo ""
    echo "📊 File info:"
    ls -lh "$OUTPUT_FILE"
    
    # Show file details
    file_size=$(du -h "$OUTPUT_FILE" | cut -f1)
    echo "   Size: $file_size"
    echo ""
    
    echo "📝 To use this texture:"
    echo "   1. Update maps/test.cub:"
    echo "      NO $OUTPUT_FILE"
    echo "      SO $OUTPUT_FILE"
    echo "      WE $OUTPUT_FILE"
    echo "      EA $OUTPUT_FILE"
    echo ""
    echo "   2. Rebuild: make re"
    echo "   3. Run: ./cub3D maps/test.cub"
    echo ""
    echo "💡 Tips for even better quality:"
    echo "   • Use well-lit photos"
    echo "   • Take photos straight-on (no angle)"
    echo "   • Get close to the wall for detail"
    echo "   • Avoid blurry photos"
else
    echo "❌ Conversion failed!"
    exit 1
fi
