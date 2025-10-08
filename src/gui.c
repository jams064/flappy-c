#include <stdlib.h>
#include <stdio.h>

#include "gui.h"

// ===================~-
// Functions
// ===================~-


// Stack related functions
void GUI_StackInit(sGuiStack* stack) {
    stack->top = -1;
    stack->max = 5;
    stack->arr = (sGuiItem*)calloc(stack->max, sizeof(sGuiItem));

    stack->init = 1;
}

int GUI_StackEmpty(sGuiStack* stack) {
    return stack->top == -1;
}

void GUI_StackPush(sGuiStack* stack, sGuiItem value) {
    int nextIndex = ++stack->top;

    if (nextIndex >= stack->max) {
        stack->max += 10;
        stack->arr = (sGuiItem*)realloc(stack->arr, sizeof(sGuiItem) * stack->max);
    }

    stack->arr[nextIndex] = value;
}

sGuiItem GUI_StackPop(sGuiStack* stack) {
    if (GUI_StackEmpty(stack)) {
        return (sGuiItem) {};
    }

    sGuiItem poppedItem = stack->arr[stack->top--];

    return poppedItem;
}

sGuiItem* GUI_StackPeek(sGuiStack* stack) {
    if (GUI_StackEmpty(stack)) {
        return NULL;
    }

    return &stack->arr[stack->top];
}

// Main GUI behavior
sGuiStack* currentStack;

void GUI_Start() {
    if (currentStack == NULL) {
        currentStack = (sGuiStack*)malloc(sizeof(sGuiStack));
    } else {
        currentStack = (sGuiStack*)realloc(currentStack, sizeof(sGuiStack));
    }
    GUI_StackInit(currentStack);
}

void GUI_Text(const char* text, Vector2 position, int xBounds, int fontSize, Color color, GUI_Align horAlignment) {
    sGuiItem *item = GUI_StackPeek(currentStack);

    if (item->type == LIST) {
        sGUIList list = item->item.list;
        printf("Dir: %i, Pad: %i, Align: %i\n", list.direction, list.padding, list.alignment);

        int textWidth = MeasureText(text, fontSize);

        int xPosition = list.x + (list.direction == DIR_HORIZONTAL ? list.currentOffset : position.x);
        int yPosition = list.y + (list.direction == DIR_VERTICAL ? list.currentOffset : position.y);

        printf("%s | %p | bOffset: %i\n", text, &list, list.currentOffset);
        list.currentOffset += (list.direction == DIR_HORIZONTAL ? textWidth : fontSize) + list.padding;
        printf("%s | aOffset: %i\n\n", text, list.currentOffset);

        DrawText(text, xPosition, yPosition, fontSize, color);
    }
}

void GUI_List(GUI_Direction direction, int padding, GUI_Align alignment, int bounds, int x, int y) {
    GUI_StackPush(currentStack, (sGuiItem) {
        .type = LIST,
        .item.list = (sGUIList) { .alignment = alignment, .direction = direction, .padding = padding, .bounds = bounds, .x = x, .y = y }
    });
}

void GUI_End() {
    if (currentStack != NULL && currentStack->init) {
        if (GUI_StackEmpty(currentStack)) {
            GUI_StackInit(currentStack);
        } else {
            GUI_StackPop(currentStack);
        }
    }
}