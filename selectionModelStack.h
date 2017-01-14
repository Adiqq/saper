#ifndef SAPER_SELECTIONMODELSTACK_H
#define SAPER_SELECTIONMODELSTACK_H
#include "model.h"

typedef struct SelectionModelStack {
    SelectionModel *contents;
    int maxSize;
    int top;
} SelectionModelStack;
void StackInit(SelectionModelStack *stackP, int maxSize);
void StackDestroy(SelectionModelStack *stackP);
void StackPush(SelectionModelStack *stackP, SelectionModel element);
SelectionModel StackPop(SelectionModelStack *stackP);
int StackIsEmpty(SelectionModelStack *stackP);
int StackIsFull(SelectionModelStack *stackP);
#endif //SAPER_SELECTIONMODELSTACK_H
