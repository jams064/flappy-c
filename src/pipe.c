#include <raylib.h>
#include <math.h>

#include "pipe.h"
#include "config.h"
#include "bird.h"

// ===================~-
// Functions
// ===================~-

void Pipe_Draw(Pipe* pipe) {
    Texture texture = pipe->texture;

    const int pWidth = texture.width;
    const int pHeight = texture.height;

    // Both Pipes

    NPatchInfo patchInfo = {(Rectangle){0.0, 0.0, pWidth, pHeight}, 2, 6, 4, 1, NPATCH_NINE_PATCH};

    const int sHeight = SCREEN_HEIGHT;
    const int sWidth = PIPE_WIDTH;

    // Bottom Pipe

    Rectangle target0 = {.x = pipe->x - pWidth, .y = pipe->y + pipe->spacing / 2, .width = sWidth, .height = sHeight};

    DrawTextureNPatch(texture, patchInfo, target0, (Vector2){.x = pWidth / 2, .y = 0}, 0, pipe->color);

    // Top Pipe

    Rectangle target1 = {.x = pipe->x + pWidth, .y = pipe->y - pipe->spacing / 2, .width = sWidth, .height = sHeight};

    DrawTextureNPatch(texture, patchInfo, target1, (Vector2){.x = pWidth / 2, .y = pHeight}, 180, pipe->color);
}

void Pipe_Update(Pipe* pipe, float speed, float delta) {
    pipe->x -= speed * delta;
}

Pipe Pipe_New(int xPosition, int yPosition, int spacing, Color color) {
    return (Pipe) {
        .x = xPosition,
        .y = yPosition,
        .spacing = spacing,
        .color = color,
        .scored = false
    };
}

PipeCollisionDirection Pipe_GetCollisionDirection(Pipe* pipe, Bird* bird) {
    float bx = bird->x;
    float by = bird->y;

    float pXmin = pipe->x - (float)PIPE_WIDTH / 2.0f - bird->w / 2;
    float pXmax = pXmin + PIPE_WIDTH;

    // Check collision on y axis
    // if the bird is NOT between the minX and maxX of the pipe
    int birdIsBeforePipe = bx < pXmin;
    int pipeIsBeforeBird = bx > pXmax;
    int insidePipe = !birdIsBeforePipe && !pipeIsBeforeBird;

    // If the bird is not inside pipe, there's no way to collide
    if (!insidePipe)
    {
        // printf("Not in X bounds: %f | %f / %f\n", bx, pXmin, pXmax);
        return DIR_NONE;
    }

    float pYmin = pipe->y - pipe->spacing / 2 + bird->h / 2;
    float pYmax = pYmin + pipe->spacing - bird->h;

    // Check collision on x axis
    // if the bird is between the minY and maxY of the pipe (Opening)

    int clearedTopPipe = by > pYmin;
    int clearedBottomPipe = by < pYmax;

    int betweenPipes = clearedTopPipe && clearedBottomPipe;

    // If bird is between the pipes, then there's no way for it to collide.
    if (betweenPipes)
    {
        return DIR_NONE;
    }

    // printf("%f | %f / %f\n", by, pYmin, pYmax);
    // println("Collides");

    // If collided on Y axis (hit sides of pipe)
    int xDirection = bird->x > pipe->x;
    int yDirection = bird->y > (pipe->y + SCREEN_HEIGHT / 2);

    int notActuallyBetweenPipes = fabs(bird->y - pYmin) > bird->h / 2 && fabs(bird->y - pYmax) > bird->h / 2;

    // If the bird is not between opening of pipes, then it must have hit the side
    if (notActuallyBetweenPipes)
    {
        // Less than 0 = left
        if (xDirection < 0)
        {
            return DIR_RIGHT;
        }
        else
        {
            return DIR_LEFT;
        }
    }
    else
    {
        // Less than 0 = top
        if (yDirection > 0)
        {
            return DIR_BOTTOM;
        }
        else
        {
            return DIR_TOP;
        }
    }
}