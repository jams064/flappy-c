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

// Helper function to draw standard raylib text centered within xBounds
void DrawTextCentered(const char* text, int xBounds, int yPosition, float fontSize, Color color);

#endif