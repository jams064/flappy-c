#ifndef INTERFACE_H
#define INTERFACE_H

#include "config.h"

// ===================~-
// Constants
// ===================~-

// Whether to render debug text on screen, comment out to disable
// #define DEBUG

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

typedef enum {
    LAYOUT_HORIZONTAL,
    LAYOUT_VERTICAL
} LayoutDirection;

typedef struct {
    Screen currentScreen;
    Screen previousScreen;
    double timeOfScreenChange;
} Interface;

typedef struct Game Game;

// ===================~-
// Functions
// ===================~-

// Draws all interface
void Interface_Draw(Interface *interface, Game* game);

// Switches the current screen
void Interface_SwitchScreen(Interface *interface, Screen screen);
// Returns the time between the screen changing, and now
float Interface_TimeSinceScreenChange(Interface* interface);

#endif