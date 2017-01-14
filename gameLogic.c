#include <stdio.h>
#include <stdlib.h>
#include "gameLogic.h"
#include "selectionModelStack.h"

#define RED   "\x1B[31m"
#define RESET "\x1B[0m"

#define MAX(a,b) ((a) > (b) ? a : b)
#define MIN(a,b) ((a) < (b) ? a : b)

Map generateEmptyMap(){
    struct Map map;
    for(int x = 0; x < 10; x++){
        for(int y = 0; y < 10; y++){
            map.map[x][y] = 0;
        }
    }
    return map;
}

void displayMap(Map map){
    for(int x = 0; x < 10; x++){
        for(int y = 0; y < 10; y++){
            printf("%d ", map.map[x][y]);
        }
        printf("\r\n");
    }
    printf("\r\n");
}

void displayUserMap(UserMap map, SelectionModel lastSelection){
    printf("\r\n");
    for(int x = 0; x < 10; x++){
        for(int y = 0; y < 10; y++){
            if(lastSelection.x == x && lastSelection.y == y){
                printf(RED "%c " RESET, map.map[x][y]);
            }else {
                printf("%c ", map.map[x][y]);
            }
        }
        printf("\r\n");
    }
    printf("\r\n");
}

UserMap createUserMap(Map mineMap, Map proximityMap, Map userHitMaskMap, int isGameEnd){
    struct UserMap map;
    for(int x = 0; x < 10; x++){
        for(int y = 0; y < 10; y++){
            if(isGameEnd){
                if (mineMap.map[x][y] == 1) {
                    map.map[x][y] = 'M';
                } else {
                    map.map[x][y] = '_';
                }
            } else {
                if (userHitMaskMap.map[x][y] == 0) map.map[x][y] = '_';
                if (userHitMaskMap.map[x][y] == 1) {
                    if (mineMap.map[x][y] == 1) {
                        map.map[x][y] = 'M';
                    } else {
                        int proximityValue = proximityMap.map[x][y];
                        char proximityChar = proximityValue + '0';
                        map.map[x][y] = proximityChar;
                    }
                }
                if (userHitMaskMap.map[x][y] == 2) {
                    int proximityValue = proximityMap.map[x][y];
                    char proximityChar = proximityValue + '0';
                    map.map[x][y] = proximityChar;
                }
            }
        }
    }
    return map;
}

SelectionModel getRandomSelection(){
    SelectionModel model;
    model.x = rand() % 10;
    model.y = rand() % 10;
    return model;
}

Map fillMapWithMines(Map map, int numOfMines){
    while(numOfMines > 0){
        SelectionModel model = getRandomSelection();
        if(map.map[model.x][model.y] == 0){
            map.map[model.x][model.y] = 1;
            numOfMines--;
        }
    }
    return map;
}

SelectionModel findUpperLeftCorner(int x, int y){
    SelectionModel model;
    model.x = MAX(x - 1, 0);
    model.y = MAX(y - 1, 0);
    return model;
}

SelectionModel findLowerRightCorner(int x, int y){
    SelectionModel model;
    model.x = MIN(x + 1, 9);
    model.y = MIN(y + 1, 9);
    return model;
}

Map createProximityMap(Map map){
    Map proximityMap = generateEmptyMap();
    for(int x = 0; x < 10; x++){
        for(int y = 0; y < 10; y++){
            SelectionModel beginCoordinates = findUpperLeftCorner(x,y);
            SelectionModel endCoordinates = findLowerRightCorner(x,y);
            int counter = 0;
            for(int x1 = beginCoordinates.x; x1 <= endCoordinates.x; x1++){
                for(int y1 = beginCoordinates.y; y1 <= endCoordinates.y; y1++){
                    if(map.map[x1][y1] == 1){
                        counter++;
                    }
                }
            }
            proximityMap.map[x][y] = counter;
        }
    }
    return proximityMap;
}

int hasMapIntersect(Map mineMap, Map userHitMap){
    for(int x = 0; x < 10; x++){
        for(int y = 0; y < 10; y++){
            if(mineMap.map[x][y] == 1 && mineMap.map[x][y] == userHitMap.map[x][y]) {
                return 1;
            }
        }
    }
    return 0;
}

SelectionModel getInteresctionPoint(Map gameMap, Map userHitMap){
    SelectionModel model;
    for(int x = 0; x < 10; x++){
        for(int y = 0; y < 10; y++){
            if(gameMap.map[x][y] == userHitMap.map[x][y]){
                model.x = x;
                model.y = y;
                return model;
            }
        }
    }
    return model;
}

int isGameWon(Map mineMap, Map userHitMap){
    int mineCount = 0;
    int notHitFields = 0;
    for(int x = 0; x < 10; x++){
        for(int y = 0; y < 10; y++){
            if(mineMap.map[x][y] == 1)mineCount++;
            if(userHitMap.map[x][y] == 0)notHitFields++;
        }
    }
    if(mineCount == notHitFields) return 1;
    return 0;
}

int isGameLost(Map mineMap, Map userHitMap){
    return hasMapIntersect(mineMap, userHitMap);
}
Map markHitAndClearNeighbours(Map proximityMap, Map userHitMap, SelectionModel model){
    //DFS
    SelectionModelStack stack;
    StackInit(&stack, 100);
    if(proximityMap.map[model.x][model.y] == 0) { //uncover other fields, only if we have area without mines
        StackPush(&stack, model);
    }
    userHitMap.map[model.x][model.y] = 1;

    while(StackIsEmpty(&stack) == 0){
        SelectionModel currentModel = StackPop(&stack);
        SelectionModel lowerBound = findUpperLeftCorner(currentModel.x, currentModel.y);
        SelectionModel upperBound = findLowerRightCorner(currentModel.x, currentModel.y);
        for(int x1 = lowerBound.x; x1 <= upperBound.x; x1++){
            for(int y1 = lowerBound.y; y1 <= upperBound.y; y1++){
                if(userHitMap.map[x1][y1] != 0) continue;
                //field is visible, but not hit
                userHitMap.map[x1][y1] = 2;
                //field has no mines nearby, automatic hit
                if(proximityMap.map[x1][y1] == 0){
                    userHitMap.map[x1][y1] = 1;
                    SelectionModel toVisitModel;
                    toVisitModel.x = x1;
                    toVisitModel.y = y1;
                    StackPush(&stack, toVisitModel);
                }
            }
        }
    }

    StackDestroy(&stack);
    return userHitMap;
}

Map addHitToMap(Map map, Map proximityMap, Map userHitMap, SelectionModel model){
    //mine hit
    if(map.map[model.x][model.y] == 1){
        userHitMap.map[model.x][model.y] = 1;
        return userHitMap;
    } else{
        return markHitAndClearNeighbours(proximityMap, userHitMap, model);
    }
}