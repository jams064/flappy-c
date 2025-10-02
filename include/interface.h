#ifndef INTERFACE_H
#define INTERFACE_H

#include "config.h"

// ===================~-
// Constants
// ===================~-

#define DEBUG

// ===================~-
// Types
// ===================~-

typedef enum {
    SCR_UNKNOWN,

    SCR_MENU,
    SCR_GAME,
    SCR_DEAD,
    SCR_PAUSE,
} Screen;

typedef struct {
    Screen currentScreen;
    double timeOfScreenChange;
} Interface;

typedef struct Game Game;

// ===================~-
// Functions
// ===================~-

void Interface_Draw(Interface *interface, Game* game);

void Interface_SwitchScreen(Interface *interface, Screen screen);
float Interface_TimeSinceScreenChange(Interface* interface);

#endif