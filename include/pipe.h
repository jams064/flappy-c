#ifndef PIPE_H
#define PIPE_H

#include <raylib.h>
#include "macro.h"

// ===================~-
// Constants
// ===================~-

// Width of pipe on screen, as well as collision
#define PIPE_WIDTH 30

// ===================~-
// Types
// ===================~-

typedef struct {
    float x, y; // X and Y Position
    unsigned byte spacing; // Spacing between top and bottom pipes
    Color color; // Color
    Texture texture;
    bool scored; // Has the bird passed through this pipe yet?
} Pipe;

typedef enum {
    DIR_NONE,
    
    DIR_LEFT,
    DIR_TOP,
    DIR_RIGHT,
    DIR_BOTTOM
} PipeCollisionDirection;

typedef struct Bird Bird;

// ===================~-
// Functions
// ===================~-

// Draws pipe
void Pipe_Draw(Pipe* pipe);
// Update pipe's position
void Pipe_Update(Pipe* pipe, float speed, float delta);

// Creates new pipe
Pipe Pipe_New(int xPosition, int yPosition, int spacing, Color color);

// Checks if bird is inside the pipe, if not returns DIR_NONE, if yes
// returns DIR_{Direction of collision}
PipeCollisionDirection Pipe_GetCollisionDirection(Pipe* pipe, Bird* bird);

#endif