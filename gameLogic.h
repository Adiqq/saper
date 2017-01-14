#ifndef SAPER_GAMELOGIC_H
#define SAPER_GAMELOGIC_H
#include "model.h"

Map generateEmptyMap();
void displayMap(Map map);
void displayUserMap(UserMap map, SelectionModel lastSelection);
Map fillMapWithMines(Map map, int numOfMines);
Map createProximityMap(Map map);
UserMap createUserMap(Map mineMap, Map proximityMap, Map userHitMaskMap, int isGameEnd);
Map addHitToMap(Map map, Map proximityMap, Map userHitMap, SelectionModel model);
int isGameWon(Map mineMap, Map userHitMap);
int isGameLost(Map mineMap, Map userHitMap);
#endif //SAPER_GAMELOGIC_H
