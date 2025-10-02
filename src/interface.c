#include <raylib.h>
#include <stdlib.h>
#include <math.h>

#include "interface.h"
#include "game.h"
#include "text.h"
#include "macro.h"

// ===================~-
// Functions
// ===================~-

static void DrawMenuScreen(Interface* interface, Game* game) {
    DrawText("Flap to play!", 5, 5, 25, WHITE);
    DrawText(TextFormat("Highscore: %i", game->saveData.highScore), 5, 30, 15, WHITE);
}

static void DrawGameScreen(Interface* interface, Game* game) {
    Color textColor = game->currentScore >= game->saveData.highScore ? YELLOW : WHITE;

    // HIGHSCORE TEXT
    DrawTextCentered(TextFormat("Highscore: %i", game->saveData.highScore), SCREEN_WIDTH, 5, 15, textColor);

    // CURRENT SCORE TEXT
    DrawTextCentered(TextFormat("%i", game->currentScore), SCREEN_WIDTH, 24, 45, ColorAlpha(ColorBrightness(textColor, -0.5), 0.9)); // Shadow
    DrawTextCentered(TextFormat("%i", game->currentScore), SCREEN_WIDTH, 20, 45, textColor); // Text

    // Flair text when you're 10 points away from beating highscore
    if (game->saveData.highScore > game->currentScore && game->saveData.highScore - game->currentScore < 10) {
        int scoreDiff = game->saveData.highScore - game->currentScore;

        DrawTextCentered(TextFormat("%i more!", scoreDiff), SCREEN_WIDTH, 65, 20, YELLOW);
    } else if (game->saveData.highScore <= game->currentScore) {
        int scoreDiff = game->currentScore - game->saveData.highScore;

        DrawTextCentered(TextFormat("+%i", scoreDiff), SCREEN_WIDTH, 65, 15, YELLOW);
    }
}

static void DrawDeathScreen(Interface* interface, Game* game) {
    float timeSinceScreenChange = Interface_TimeSinceScreenChange(interface);

    // GAME OVER TEXT
    DrawTextCentered("Game over!", SCREEN_WIDTH, 5, 30, (Color) {255, 100, 100, clamp(timeSinceScreenChange * 2 * 255, 0, 255) });

    // SCORE TEXT
    if (timeSinceScreenChange > 0.5f) {
        DrawTextCentered(TextFormat("Score: %i", game->currentScore), SCREEN_WIDTH, 35, 20, (Color) {255, 255, 200, clamp((timeSinceScreenChange - 0.5) * 2 * 255, 0, 255) });
    } else { return; }

    // NEW HIGHSCORE TEXT
    if (game->currentScore > game->saveData.highScore && timeSinceScreenChange > 2.0f) {
        DrawTextCentered("New highscore!", SCREEN_WIDTH, 65 + sinf(timeSinceScreenChange * 2) * 5, 20, YELLOW);
    }

    // PLAY AGAIN TEXT
    if (GetTimeSinceDeath(game) > 2.0f) {
        int rb = ((sin(timeSinceScreenChange * 3) + 1) / 2) * (255 - 100) + 100;
        Color textColor = {rb, 255, rb, 255};

        DrawTextCentered("Flap to play again!", SCREEN_WIDTH, SCREEN_HEIGHT*0.75 + 2, 20, ColorBrightness(textColor, -0.5)); // Shadow
        DrawTextCentered("Flap to play again!", SCREEN_WIDTH, SCREEN_HEIGHT*0.75, 20, textColor);
    }
}

void Interface_Draw(Interface *interface, Game* game) {
    switch (interface->currentScreen) {
        case (SCR_MENU): DrawMenuScreen(interface, game); break;

        case (SCR_GAME): DrawGameScreen(interface, game); break;

        case (SCR_DEAD): DrawDeathScreen(interface, game); break;

        default: {}break;
    } 

    #ifdef DEBUG

        // PLAYER POSITION AND VELOCITY TEXT
        DrawText(TextFormat("by: %.2f", game->bird.y), 4, 4, 15, WHITE); // Position
        DrawText(TextFormat("bv: %.2f", game->bird.v), 4, 4+15, 15, WHITE); // Velocity

    #endif
}

void Interface_SwitchScreen(Interface *interface, Screen screen) {
    interface->currentScreen = screen;
    interface->timeOfScreenChange = GetTime();
}

float Interface_TimeSinceScreenChange(Interface *interface) {
    return GetTime() - interface->timeOfScreenChange;
}