#ifndef GUI_H
#define GUI_H

#include <raylib.h>

// ===================~-
// Types
// ===================~-

typedef enum {
    DIR_HORIZONTAL,
    DIR_VERTICAL
} GUI_Direction;

typedef enum {
    ALIGN_START,
    ALIGN_CENTER,
    ALIGN_END
} GUI_Align;

typedef struct {
    GUI_Direction direction;
    GUI_Align alignment;
    int padding;
} sGUIList;

typedef struct {
    enum {
        typUndefined,
        typList,
        typPadding
    };

    void* value;
} sGuiItem;

typedef struct {
    sGuiItem* arr;
    int top;
    int max;

    int init;
} sGuiStack;

// ===================~-
// Variables
// ===================~-


// ===================~-
// Functions
// ===================~-

// Stack functions
void GUI_StackInit(sGuiStack* stack);
int GUI_StackEmpty(sGuiStack* stack);

void GUI_StackPush(sGuiStack* stack, sGuiItem value);
void GUI_StackPop(sGuiStack* stack);
void GUI_StackPeek(sGuiStack* stack);

// GUI functions
void GUI_Start();

void GUI_Text(const char* text, Vector2 position, int xBounds, int fontSize, Color color, GUI_Align horAlignment);

void GUI_List(GUI_Direction direction, int padding, GUI_Align alignment, int bounds, int x, int y);
void GUI_End();

#endif