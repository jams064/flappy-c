#ifndef SAVE_H
#define SAVE_H

#include <raylib.h>

// ===================~-
// Constants
// ===================~-

#define SAVE_VERSION 1

// ===================~-
// Types
// ===================~-

typedef struct {
    int version;

    int highScore;
    Color birdColor;
} SaveData;

// ===================~-
// Functions
// ===================~-

void LoadSaveData(SaveData* save, const char* fileName);
void SaveSaveData(SaveData* save, const char* fileName);

#endif