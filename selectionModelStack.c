#include <stdio.h>
#include <stdlib.h>
#include "selectionModelStack.h"
void StackInit(SelectionModelStack *stackP, int maxSize)
{
    SelectionModelStack *newContents;
    newContents = (SelectionModelStack *)malloc(sizeof(SelectionModelStack) * maxSize);

    if (newContents == NULL) {
        fprintf(stderr, "Insufficient memory to initialize stack.\n");
        exit(1);
    }

    stackP->contents = newContents;
    stackP->maxSize = maxSize;
    stackP->top = -1;  /*empty */
}

void StackDestroy(SelectionModelStack *stackP)
{
    free(stackP->contents);

    stackP->contents = NULL;
    stackP->maxSize = 0;
    stackP->top = -1;  /*empty */
}

void StackPush(SelectionModelStack *stackP, SelectionModel element)
{
    if (StackIsFull(stackP)) {
        fprintf(stderr, "Can't push element on stack: stack is full.\n");
        exit(1);
    }
    stackP->contents[++stackP->top] = element;
}

SelectionModel StackPop(SelectionModelStack *stackP)
{
    if (StackIsEmpty(stackP)) {
        fprintf(stderr, "Can't pop element from stack: stack is empty.\n");
        exit(1);
    }

    return stackP->contents[stackP->top--];
}

int StackIsEmpty(SelectionModelStack *stackP)
{
    return stackP->top < 0;
}
int StackIsFull(SelectionModelStack *stackP)
{
    return stackP->top >= stackP->maxSize - 1;
}