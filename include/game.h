#ifndef GAME_H
#define GAME_H

#include <raylib.h>

#include "bird.h"
#include "pipe.h"
#include "save.h"
#include "interface.h"
#include "config.h"

// ===================~-
// Constants
// ===================~-

#define FLOOR_POSITION SCREEN_HEIGHT - FLOOR_OFFSET

// ===================~-
// Types
// ===================~-

typedef enum {
    GS_WAITING,
    GS_RUNNING,
    GS_ENDED,
    GS_PAUSED
} GameState;

typedef struct {
    Texture bird;
    Texture pipe;
    Texture ground;
} Textures;

typedef struct Game {
    Pipe pipes[MAX_PIPES];
    Bird bird;

    Textures textures;
    SaveData saveData;
    Interface interface;
    
    float lastPipeSpawnPosition;
    int currentPipeIndex;

    GameState state;

    float speed;
    float position;

    double timeOfDeath;

    int currentScore;

    char* saveFileName;
} Game;

// ===================~-
// Functions
// ===================~-

void InitGame(Game* game);
void DeInitGame(Game* game);

void LoadTextures(Game* game);
void UnloadTextures(Game* game);

void ProcessInputs(Game* game);
void UpdateGame(Game* game);
void DrawGame(Game* game);

void AddPipe(Game* game, Pipe* pipe, int index);

void SetSaveFileName(Game* game, char* name);

// Returns time since the bird died,
// if the bird is alive, returns -1
float GetTimeSinceDeath(Game* game);

#endif