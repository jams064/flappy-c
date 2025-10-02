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

void Bird_Jump(Bird* bird);
void Bird_Kill(Bird* bird);

void Bird_Update(Bird* bird, float delta);
void Bird_Draw(Bird* bird);

void Bird_CycleColor(Bird* bird);

#endif