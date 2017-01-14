#ifndef SAPER_MODEL_H
#define SAPER_MODEL_H
typedef struct SelectionModel{
    int x;
    int y;
} SelectionModel;
typedef struct Map {
    int map[10][10];
} Map;
typedef struct UserMap {
    char map[10][10];
} UserMap;
#endif //SAPER_MODEL_H
