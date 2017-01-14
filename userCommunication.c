#include <stdio.h>
#include "userCommunication.h"

int hasInvalidRange(SelectionModel model){
    return model.x < 0 ||
           model.x > 9 ||
           model.y < 0 ||
           model.y > 9;
}

int isAlreadyHit(SelectionModel model, Map userHitMap) {
    if(!hasInvalidRange(model)) {
        int value = userHitMap.map[model.x][model.y];
        if (value != 0) return 1;
    }
    return 0;
}

SelectionModel getUserSelectionWithValidation(Map userHitMap){
    SelectionModel model = getUserSelection();
    int alreadyHit = isAlreadyHit(model, userHitMap);
    while(hasInvalidRange(model) || alreadyHit){
        if(alreadyHit){
            fprintf(stderr, "Field is already discovered!\r\n");
        }else {
            fprintf(stderr, "Invalid value range. Format:int int. Valid range [0-9]\r\n");
        }
        model = getUserSelection();
        alreadyHit = isAlreadyHit(model, userHitMap);
    }
    return model;
}

SelectionModel getUserSelection(){
    int result = 0;
    char userInput[100];
    SelectionModel model;
    while(result != 2) {
        printf("Select field (eg. 0 0)\r\n");
        fgets(userInput, sizeof(userInput), stdin);
        result = sscanf(userInput, "%d %d", &model.x, &model.y);
    }
    return model;
}