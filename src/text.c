#include <raylib.h>

#include "text.h"

// ===================~-
// Functions
// ===================~-

void Text(const char* text, int xPos, int yPos, int fontSize, Color color) {
    int shadowOffset = fontSize/10;

    if (shadowOffset > 1) DrawText(text, xPos, yPos + shadowOffset, fontSize, ColorBrightness(color, -0.4)); // SHADOW
    DrawText(text, xPos, yPos, fontSize, color); // TEXT
}

void TextCentered(const char* text, int xBounds, int yPos, int fontSize, Color color) {
    int w = MeasureText(text, fontSize);

    Text(text, xBounds / 2 - w / 2, yPos, fontSize, color);
}