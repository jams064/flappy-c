#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game.h"
#include "resource_dir.h"

// ===================~-
// Functions
// ===================~-

char* join_path(const char* path1, const char* path2) {
    char* result = malloc(strlen(path1) + strlen(path2) + 2);
    strcpy(result, path1);
    strcat(result, "/");
    strcat(result, path2);
    return result;
}

// ===================~-
// Entry
// ===================~-

void MainLoop(Game* game);

int main(void)
{
    char *saveFileName = join_path(GetApplicationDirectory(), "flappysave.bin");

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Flappy C");
    SearchAndSetResourceDir("resources");

    Game *game = (Game *)calloc(1, sizeof(Game));

    SetSaveFileName(game, saveFileName);
    LoadSaveData(&game->saveData, saveFileName);

    InitGame(game);

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        MainLoop(game);
    }

    DeInitGame(game);
    free(saveFileName);

    CloseWindow();

    return 0;
}

// ========================

void MainLoop(Game* game) {
    UpdateGame(game);

    // Render
    BeginDrawing();

        DrawGame(game);

    EndDrawing();
}