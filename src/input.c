#include <raylib.h>

#include "input.h"

// ===================~-
// Functions
// ===================~-

bool IsMainActionPressed() {
    return IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_UP);
}