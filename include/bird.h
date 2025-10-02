#ifndef BIRD_H
#define BIRD_H

#include <raylib.h>

// ===================~-
// Constants
// ===================~-

#define JUMP_VELOCITY 3.0f

extern const Color birdColors[];

// ===================~-
// Types
// ===================~-

typedef struct Bird {
    float x, y, tx; // X Position, Y Position, and Target X Position (For Interpolation)
    float w, h; // Width & Height
    float v; // Velocity
    bool alive; // Is bird alive?
    Color color;
    Texture texture;
} Bird;

// ===================~-
// Functions
// ===================~-

// Makes bird jump
void Bird_Jump(Bird* bird);
// Kills bird
void Bird_Kill(Bird* bird);

// Update bird position & velocity
void Bird_Update(Bird* bird, float delta);
// Draw bird
void Bird_Draw(Bird* bird);

// Cycles bird color
void Bird_CycleColor(Bird* bird);

#endif