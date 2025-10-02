#include <raylib.h>

#include "text.h"

// ===================~-
// Functions
// ===================~-

void DrawTextCentered(const char* text, int xBounds, int yPosition, float fontSize, Color color) {
    int w = MeasureText(text, fontSize);

    DrawText(text, xBounds / 2 - w / 2, yPosition, fontSize, color);
}