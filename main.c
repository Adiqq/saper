#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "userCommunication.h"
#include "gameLogic.h"
#define DEBUG 0
#define RANDOM_MINES 1

void showDebug(Map mineMap, Map proximityMap, Map userHitMap){
    if(DEBUG) {
        printf("Displaying mine mineMap:\r\n");
        displayMap(mineMap);
        printf("Displaying proximity mineMap:\r\n");
        displayMap(proximityMap);
        printf("Displaying user hit mineMap:\r\n");
        displayMap(userHitMap);
    }
}

int main() {
    if(RANDOM_MINES) srand(time(NULL));
    Map mineMap = generateEmptyMap();
    Map proximityMap;
    Map userHitMap = generateEmptyMap();
    mineMap = fillMapWithMines(mineMap, 8);
    proximityMap = createProximityMap(mineMap);
    SelectionModel model;
    int isEnd = 0;
    int gameLost = 0;
    int gameWon = 0;
    while(!isEnd){
        showDebug(mineMap, proximityMap, userHitMap);
        displayUserMap(createUserMap(mineMap,proximityMap,userHitMap, isEnd), model);
        model = getUserSelectionWithValidation(userHitMap);
        printf("Field selected: (%d,%d)\r\n", model.x, model.y);
        userHitMap = addHitToMap(mineMap, proximityMap, userHitMap, model);

        gameLost = isGameLost(mineMap, userHitMap);
        gameWon = isGameWon(mineMap, userHitMap);
        if(gameLost || gameWon) isEnd = 1;

        if(gameWon){
            printf("You have won!\r\n");
            displayUserMap(createUserMap(mineMap,proximityMap,userHitMap, isEnd), model);
            showDebug(mineMap, proximityMap, userHitMap);
        } else if(gameLost){
            printf("You have lost!\r\n");
            displayUserMap(createUserMap(mineMap,proximityMap,userHitMap, isEnd), model);
            showDebug(mineMap, proximityMap, userHitMap);
        }
    }
    char *ch;
    printf("Type anything + ENTER to exit\r\n");
    scanf("%s",&ch);//wait for exit
    return 0;
}