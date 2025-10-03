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
    // FLAP TO PLAY TEXT
    Text("Flap to play!", 5, 5, 25, WHITE);

    // HIGHSCORE TEXT
    Text(TextFormat("Highscore: %i", game->saveData.highScore), 5, 30, 15, YELLOW);

    // CONTROLS
    Text("(Left Click) / [Up] / [Space]", 4, SCREEN_HEIGHT-(15+19+20), 12, WHITE);
    Text("to Flap", 4, SCREEN_HEIGHT-(19+20), 15, WHITE);
    Text("[P] to Pause", 4, SCREEN_HEIGHT-19, 15, WHITE);
    // Text("[P] to Pause", 4, SCREEN_HEIGHT-19, 15, WHITE);
}

static void DrawGameScreen(Interface* interface, Game* game) {
    Color textColor = game->currentScore >= game->saveData.highScore ? YELLOW : WHITE;

    // HIGHSCORE TEXT
    TextCentered(TextFormat("Highscore: %i", game->saveData.highScore), SCREEN_WIDTH, 5, 15, textColor);

    // CURRENT SCORE TEXT
    float timeSinceScore = GetTime() - game->timeOfScore;
    float prog = clamp(timeSinceScore * 2, 0, 1);
    TextCentered(TextFormat("%i", game->currentScore), SCREEN_WIDTH, 20, (lerp(50, 45, prog)), ColorLerp(YELLOW, textColor, prog)); // Text

    // Flair text when you're 10 points away from beating highscore
    if (game->saveData.highScore > game->currentScore && game->saveData.highScore - game->currentScore < 10) {
        int scoreDiff = game->saveData.highScore - game->currentScore;

        TextCentered(TextFormat("%i more!", scoreDiff), SCREEN_WIDTH, 65, 20, YELLOW);
    } else if (game->saveData.highScore <= game->currentScore) {
        int scoreDiff = game->currentScore - game->saveData.highScore;

        TextCentered(TextFormat("+%i", scoreDiff), SCREEN_WIDTH, 65, 15, YELLOW);
    }
}

static void DrawDeathScreen(Interface* interface, Game* game) {
    float timeSinceScreenChange = Interface_TimeSinceScreenChange(interface);

    // GAME OVER TEXT
    TextCentered("Game over!", SCREEN_WIDTH, 15, 30, (Color) {255, 100, 100, clamp(timeSinceScreenChange * 2 * 255, 0, 255) });

    // SCORE TEXT
    if (timeSinceScreenChange > 0.5f) {
        TextCentered(TextFormat("Score: %i", game->currentScore), SCREEN_WIDTH, 45, 20, (Color) {255, 255, 200, clamp((timeSinceScreenChange - 0.5) * 2 * 255, 0, 255) });
    } else { return; }

    // NEW HIGHSCORE TEXT
    if (game->currentScore > game->saveData.highScore && timeSinceScreenChange > 2.0f) {
        TextCentered("New highscore!", SCREEN_WIDTH, 75 + sinf(timeSinceScreenChange * 2) * 5, 20, YELLOW);
    }

    // PLAY AGAIN TEXT
    if (GetTimeSinceDeath(game) > 2.0f) {
        int rb = ((sin(timeSinceScreenChange * 3) + 1) / 2) * (255 - 100) + 100;
        Color textColor = {rb, 255, rb, 255};

        TextCentered("Flap to play again!", SCREEN_WIDTH, SCREEN_HEIGHT*0.75, 20, textColor);
    }
}

static void DrawPauseScreen(Interface* interface, Game* game) {
    TextCentered("Paused!", SCREEN_WIDTH, 15, 30, WHITE);
    TextCentered(TextFormat("Score: %i", game->currentScore), SCREEN_WIDTH, 45, 20, YELLOW);

    TextCentered("[P] to Unpause", SCREEN_WIDTH, SCREEN_HEIGHT * 0.8, 20, WHITE);
}

void Interface_Draw(Interface *interface, Game* game) {
    switch (interface->currentScreen) {
        case (SCR_MENU): DrawMenuScreen(interface, game); break;

        case (SCR_GAME): DrawGameScreen(interface, game); break;

        case (SCR_DEAD): DrawDeathScreen(interface, game); break;

        case (SCR_PAUSE): DrawPauseScreen(interface, game); break;

        default: {}break;
    } 

    #ifdef DEBUG

        // PLAYER POSITION AND VELOCITY TEXT
        Text(TextFormat("by: %.2f", game->bird.y), 4, 4, 15, WHITE); // Position
        Text(TextFormat("bv: %.2f", game->bird.v), 4, 4+15, 15, WHITE); // Velocity

    #endif
}

void Interface_SwitchScreen(Interface *interface, Screen screen) {
    interface->previousScreen = interface->currentScreen;
    interface->currentScreen = screen;
    interface->timeOfScreenChange = GetTime();
}

float Interface_TimeSinceScreenChange(Interface *interface) {
    return GetTime() - interface->timeOfScreenChange;
}