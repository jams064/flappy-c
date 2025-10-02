#include <stdio.h>
#include <raylib.h>

#include "save.h"

// ===================~-
// Functions
// ===================~-

void LoadSaveData(SaveData* save, const char* fileName) {
    FILE* saveFilePointer = fopen(fileName, "rb");
    if (saveFilePointer == NULL) {
        *save = (SaveData) {
            .version = SAVE_VERSION,
            .highScore = 0,
            .birdColor = WHITE
        };

        return;
    }

    fread(save, sizeof(SaveData), 1, saveFilePointer);
    fclose(saveFilePointer);

    switch (save->version) {
        case (1): {
            if (ColorIsEqual(save->birdColor, BLANK)) {
                save->birdColor = WHITE;
            }
        }
    }
}

void SaveSaveData(SaveData* save, const char* fileName) {
    FILE* saveFilePointer = fopen(fileName, "wb");

    if (saveFilePointer == NULL) {
        return;
    }

    fwrite(save, sizeof(SaveData), 1, saveFilePointer);
    fclose(saveFilePointer);
}