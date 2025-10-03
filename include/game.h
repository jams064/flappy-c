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

#define MIN_PIPE_Y SCREEN_HEIGHT*0.2
#define MAX_PIPE_Y SCREEN_HEIGHT*0.7

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

typedef struct {
    Sound flap;
    Sound hit;
    Sound die;
    Sound score;
} Sounds;

typedef struct Game {
    Pipe pipes[MAX_PIPES]; // Pipe array
    Bird bird; // Bird (Player)

    Textures textures; // Texture struct
    SaveData saveData; // Save data
    Interface interface; // Interface struct
    Sounds sounds; // Sounds struct
    
    float lastPipeSpawnPosition; // Position of last pipe spawn (x)
    int lastPipeY; // Height of last pipe spawn (y)

    unsigned int currentPipeIndex; // Current index of pipe array, wraps around

    GameState state; // State of game

    float speed; // Speed of scrolling
    float position; // Current scroll position

    unsigned int currentScore; // Score
    float timeOfScore; // Time that last score

    char* saveFileName; // Name of save file to save and load
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

// Pauses the game
void PauseGame(Game* game);

// Resumes the game after a pause
void ResumeGame(Game* game);

// Loads textures, load data, and calls ResetGame
void InitGame(Game* game);

// Unloads textures, saves data, and frees game struct from memory
void DeInitGame(Game* game);

// Loads all textures needed by the game
void LoadTextures(Game* game);

// Unloads all textures loaded by LoadTextures
void UnloadTextures(Game* game);

// Loads all sounds needed by the game
void LoadSounds(Game* game);

// Unloads all sounds loaded by LoadSounds
void UnloadSounds(Game* game);

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