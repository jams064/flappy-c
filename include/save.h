#ifndef SAVE_H
#define SAVE_H

#include <raylib.h>

// ===================~-
// Constants
// ===================~-

// Current version of save file, not sure this will be used
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

// Loads save data, as well as reconciling savedata struct with default data if no file found
void LoadSaveData(SaveData* save, const char* fileName);
// Saves data to file.
void SaveSaveData(SaveData* save, const char* fileName);

#endif