#ifndef TEXT_H
#define TEXT_H

#include <raylib.h>

// ===================~-
// Types
// ===================~-

typedef enum {
    TOP,
    BOTTOM,
    CENTER,
} VerticalAlignment;

// ===================~-
// Functions
// ===================~-

void DrawTextCentered(const char* text, int xBounds, int yPosition, float fontSize, Color color);

#endif