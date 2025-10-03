#include <raylib.h>
#include <math.h>
#include <stdio.h>

#include "bird.h"
#include "game.h"
#include "macro.h"

// ===================~-
// Constants
// ===================~-

const Color birdColors[] = {
    WHITE,
    RED,
    ORANGE,
    YELLOW,
    GREEN,
    BLUE,
    PINK,
    BLACK
};

// ===================~-
// Functions
// ===================~-

void Bird_Jump(Bird* bird) {
    bird->v = -JUMP_VELOCITY;
}

void Bird_Kill(Bird* bird) {
    if (bird->alive) {
        bird->alive = false;
        bird->timeOfDeath = GetTime();
    }
}

float Bird_GetTimeSinceDeath(Bird* bird) {
    if (bird->alive) { return -1.0f; };

    return GetTime() - bird->timeOfDeath;
}

void Bird_Update(Bird* bird, float delta) {
    // Check that bird is above ground
    if ((int)bird->y < FLOOR_POSITION) {
        bird->v += GRAVITY * delta;
    }
    
    bird->y += bird->v;

    // Lerp x to target position
    if (fabs(bird->x - bird->tx) < 1) {
        bird->x = bird->tx;
    } else {
        bird->x = lerp(bird->x, bird->tx, delta);
    }

    bool birdBelowFloor = bird->y > FLOOR_POSITION;
    bool birdOnFloor = bird->y >= FLOOR_POSITION;

    if (bird->y <= 0 /* Bird is above screen */ || birdOnFloor) {
        Bird_Kill(bird);

        // Make the bird "bounce"
        if (birdOnFloor) {
            if (birdBelowFloor) {
                bird->v *= -0.5f;
            } else {
                bird->v = 0.0f;
            }

            bird->y = FLOOR_POSITION;
        }
    }
}

void Bird_Draw(Bird* bird) {
    Texture texture = bird->texture;

    const int bWidth = texture.width;
    const int bHeight = texture.height;

    Rectangle source = {.x = 0, .y = 0, .width = bWidth, .height = bHeight};

    float wFac = bird->w / bWidth;
    float hFac = bird->h / bHeight;

    Rectangle target = {.x = bird->x, .y = bird->y, .width = bWidth * wFac, .height = bHeight * hFac};
    Vector2 origin = {.x = bWidth / 2, .y = bHeight / 2};

    Color color = bird->alive ? bird->color : ColorLerp(bird->color, RED, clamp(Bird_GetTimeSinceDeath(bird), 0, 1));

    DrawTexturePro(texture, source, target, origin, bird->v * 7, color);
}

void Bird_CycleColor(Bird* bird) {
    bird->color = WHITE;
    //TODO: DO THIS 
}