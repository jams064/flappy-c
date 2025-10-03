#include <raylib.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

#include "game.h"
#include "bird.h"
#include "pipe.h"
#include "input.h"
#include "interface.h"
#include "macro.h"

// ===================~-
// Functions
// ===================~-

void ResetGame(Game* game) {
    if (game->currentScore > game->saveData.highScore) {
        game->saveData.highScore = game->currentScore;
    }

    game->bird = (Bird) {
        .alive = true,
        .color = game->saveData.birdColor,

        .h = 15, .w = 20,
        .x = SCREEN_WIDTH/2, .y = SCREEN_HEIGHT/2, .tx = SCREEN_WIDTH/2,
        .v = 0,

        .texture = game->textures.bird
    };

    game->currentPipeIndex = 0;
    game->lastPipeSpawnPosition = 0.0f;
    game->currentScore = 0;
    game->timeOfScore = 0;

    game->interface = (Interface) {
        .previousScreen = SCR_UNKNOWN,
        .currentScreen = SCR_UNKNOWN,
        .timeOfScreenChange = GetTime()
    };
    
    game->position = 0.0f;
    game->speed = 60.0f * 2.0f;
    game->state = GS_WAITING;

    // Clear pipes
    memset(&game->pipes, 1, sizeof(game->pipes));

    // Other
    Interface_SwitchScreen(&game->interface, SCR_MENU);
}

void StartGame(Game* game) {
    game->state = GS_RUNNING;
    game->bird.tx = 30;

    Interface_SwitchScreen(&game->interface, SCR_GAME);
}

void EndGame(Game* game) {
    game->state = GS_ENDED;

    Interface_SwitchScreen(&game->interface, SCR_DEAD);
}

void Score(Game* game) {
    game->currentScore++;
    game->timeOfScore = GetTime();
}

void InitGame(Game* game) {
    LoadTextures(game);
    LoadSaveData(&game->saveData, game->saveFileName);

    ResetGame(game);
}

void DeInitGame(Game* game) {
    UnloadTextures(game);
    SaveSaveData(&game->saveData, game->saveFileName);

    free(game);
}

void LoadTextures(Game* game) {
    game->textures = (Textures) {
        .bird = LoadTexture("bird.png"),
        .pipe = LoadTexture("pipeNsegX.png"),
        .ground = LoadTexture("ground.png"),
    };
}

void UnloadTextures(Game* game) {
    UnloadTexture(game->textures.bird);
    UnloadTexture(game->textures.pipe);
    UnloadTexture(game->textures.ground);
}

void UpdateGame(Game* game) {
    float delta = GetFrameTime();

    // Update game state
    if (!game->bird.alive && game->state == GS_RUNNING) { EndGame(game); }

    // Process inputs
    ProcessInputs(game);

    if (game->state == GS_PAUSED) { return; }

    // Update position
    game->position += game->speed * delta;

    if (game->state == GS_ENDED) {
        game->speed = lerp(game->speed, 0, delta);
    }
    // printf("%f, %f", game->position, game->pipes[0].x);

    // Update bird and pipes
    Bird_Update(&game->bird, delta);
    if (game->state == GS_RUNNING) {
        // Check whether pipe can spawn and spawn if so
        if (game->position - game->lastPipeSpawnPosition > 150 /* Pipe spawn distance*/) {
            game->lastPipeSpawnPosition = game->position;

            Pipe newPipe = Pipe_New(
                SCREEN_WIDTH + PIPE_WIDTH*2, 
                GetRandomValue(SCREEN_HEIGHT*0.2, SCREEN_HEIGHT*0.7), 
                GetRandomValue(60, 70), 
                (Color) { 100, 255, 100, 255 }
            );
            AddPipe(game, &newPipe, game->currentPipeIndex++);
            game->currentPipeIndex = game->currentPipeIndex % MAX_PIPES;
        }
    } else if (game->state == GS_WAITING) {
        // Do bird AI (ok)

        if ((game->bird.y > SCREEN_HEIGHT * 0.25 && chance(40)) || game->bird.y > SCREEN_HEIGHT * 0.7) {
            Bird_Jump(&game->bird);
        }
    }

    // Update pipes
    for (int i = 0; i < MAX_PIPES; i++) {
        Pipe *pipe = &game->pipes[i];
        
        Pipe_Update(pipe, game->speed, delta);

        if (game->state != GS_RUNNING) { continue; }

        PipeCollisionDirection collision = Pipe_GetCollisionDirection(pipe, &game->bird);
        if (collision != DIR_NONE) {
            Bird_Kill(&game->bird);

            switch (collision) {
                case DIR_LEFT:
                    // println("Left");
                    game->speed *= -0.75;
                    break;

                case DIR_RIGHT:
                    // println("Right");
                    break;

                case DIR_TOP:
                    // println("Bottom");
                    game->bird.v = fabs(game->bird.v) * -0.75;
                    break;

                case DIR_BOTTOM:
                    // println("Top");
                    game->bird.v = fabs(game->bird.v) * 0.9;
                    break;

                default:
                    break;
            }
        } 

        // Check if pipe passed player this step
        if (
            pipe->x <= game->bird.x && // Pipe is past the bird
            !pipe->scored
        ) {
            Score(game);
            pipe->scored = true;
        }
    }
}

void ProcessInputs(Game* game) {
    bool mainActionPressed = IsMainActionPressed();

    if (mainActionPressed) {
        if (game->state == GS_WAITING) {
            StartGame(game);
            Bird_Jump(&game->bird);
        } else if (game->state == GS_RUNNING) {
            Bird_Jump(&game->bird);
        } else if (game->state == GS_ENDED && GetTimeSinceDeath(game) > 2.0f) {
            ResetGame(game);
        }
    }
}

static void DrawGround(Game* game) {
    Texture groundTexture = game->textures.ground;

    int textureWidth = groundTexture.width;
    int textureHeight = groundTexture.height;

    float scale = FLOOR_OFFSET / textureHeight;

    float screenWidth = textureWidth * scale;
    float screenHeight = (float)FLOOR_OFFSET;

    int tileCount = (int)ceilf(SCREEN_WIDTH / screenWidth);

    for (int i = 0; i <= tileCount; i++) {
        DrawTexturePro(
            groundTexture,
            (Rectangle) { 0, 0, textureWidth, textureHeight },
            (Rectangle) { i * screenWidth + -((int)game->position % (int)screenWidth), FLOOR_POSITION, screenWidth, screenHeight },
            (Vector2) { 0, 0 },
            0,
            WHITE
        );
    }
}

void DrawGame(Game* game) {
    ClearBackground(BLUE);

    // !!! Order matters
    // Pipes
    for (int i = 0; i < MAX_PIPES; i++) {
        Pipe* pipe = &game->pipes[i];

        // printf("%f", pipe->y);
        Pipe_Draw(pipe);
    }

    DrawGround(game);
    Bird_Draw(&game->bird);

    Interface_Draw(&game->interface, game);
}

void AddPipe(Game* game, Pipe *pipe, int index) {
    pipe->texture = game->textures.pipe;
    game->pipes[index] = *pipe;
}

void SetSaveFileName(Game* game, char* name) {
    game->saveFileName = name;
}

float GetTimeSinceDeath(Game* game) {
    return Bird_GetTimeSinceDeath(&game->bird);
}