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

// Position of ground on screen
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

    int currentScore;
    float timeOfScore;

    char* saveFileName;
} Game;

// ===================~-
// Functions
// ===================~-

// Resets all members of provided game struct
// to initial states
void ResetGame(Game* game);

// Starts the game, sets state to running and
// interface to game screen
void StartGame(Game* game);

// Ends the game, sets interface to death screen
void EndGame(Game* game);

// Loads textures, load data, and calls ResetGame
void InitGame(Game* game);

// Unloads textures, saves data, and frees game struct from memory
void DeInitGame(Game* game);

// Loads all textures needed by the game
void LoadTextures(Game* game);

// Unloads all textures loaded by LoadTextures
void UnloadTextures(Game* game);

// Handles game inputs
void ProcessInputs(Game* game);

// Updates game states, and entities
void UpdateGame(Game* game);

// Renders game
void DrawGame(Game* game);

// Adds pipe to game
void AddPipe(Game* game, Pipe* pipe, int index);

// Sets file name to save and load from
void SetSaveFileName(Game* game, char* name);

// Returns time since the bird died,
// if the bird is alive, returns -1
float GetTimeSinceDeath(Game* game);

#endif