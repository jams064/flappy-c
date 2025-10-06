#include <stdlib.h>

#include "gui.h"

// ===================~-
// Functions
// ===================~-


// Stack related functions
void GUI_StackInit(sGuiStack* stack) {
    stack->top = -1;
    stack->max = 5;
    stack->arr = (sGuiItem*)malloc(stack->top*sizeof(sGuiItem));

    stack->init = 1;
}

int GUI_StackEmpty(sGuiStack* stack) {
    return stack->top == -1;
}

void GUI_StackPush(sGuiStack* stack, sGuiItem value) {
    stack->arr[++stack->top] = value;

    if (stack->top >= stack->max) {
        stack->max += 10;
        realloc(stack->arr, sizeof(sGuiItem) * stack->max);
    }
}

sGuiItem GUI_StackPop(sGuiStack* stack) {
    if (GUI_StackEmpty(stack)) {
        return;
    }

    sGuiItem poppedItem = stack->arr[stack->top];

    stack->top--;

    return poppedItem;
}

sGuiItem GUI_StackPeek(sGuiStack* stack) {
    if (GUI_StackEmpty(stack)) {
        return;
    }

    return stack->arr[stack->top];
}

// Main GUI behavior
sGuiStack* currentStack;

void GUI_Start() {
    if (currentStack->init) {
        free(currentStack->arr);
        free(currentStack);
    }

    currentStack = (sGuiStack*)malloc(sizeof(sGuiStack));
    GUI_StackInit(currentStack);
}