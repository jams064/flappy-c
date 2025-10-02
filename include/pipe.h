#ifndef PIPE_H
#define PIPE_H

#include <raylib.h>

// ===================~-
// Constants
// ===================~-

#define PIPE_WIDTH 30

// ===================~-
// Types
// ===================~-

typedef struct {
    float x, y; // X and Y Position
    int spacing; // Spacing between top and bottom pipes
    Color color; // Color
    Texture texture;
    bool scored;
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

void Pipe_Draw(Pipe* pipe);
void Pipe_Update(Pipe* pipe, float speed, float delta);

Pipe Pipe_New(int xPosition, int yPosition, int spacing, Color color);

PipeCollisionDirection Pipe_GetCollisionDirection(Pipe* pipe, Bird* bird);

#endif