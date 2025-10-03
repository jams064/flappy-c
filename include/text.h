#ifndef TEXT_H
#define TEXT_H

#include <raylib.h>

// ===================~-
// Types
// ===================~-

// Unused, maybe?
typedef enum {
    TOP,
    BOTTOM,
    CENTER,
} VerticalAlignment;

// ===================~-
// Functions
// ===================~-

// Draws text in styled way
void Text(const char* text, int x, int y, int fontSize, Color color);

// Helper function to draw standard raylib text centered within xBounds
void TextCentered(const char* text, int xBounds, int yPosition, int fontSize, Color color);

#endif