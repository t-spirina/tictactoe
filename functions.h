#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <random>

#define CHECK_DOT(X,Z) (((X) >= 0) && ((X) < (Z)))
#define POINT_ITEM(a,r,c) (*((*((a) + (r))) + (c)))
#define SIZE_ARRAY(a) ((sizeof(a)) / (sizeof(a[0])))
#define GET_MAX(a,b) ((a)>(b))? (a):(b)
#define GET_MIN(a,b) ((a)<(b))? (a):(b)


// subjects

enum PLAYER {HUMAN='X', AI='O', EMPTY='_'};
enum GameState {WIN, NOTWIN, DRAW};
enum scores {AIscore=-1, DRAWscore=0, HUMANscore=1};
typedef struct {
    int szX;
    int szY;
    PLAYER **map;
    int toWin;
} Field;

typedef struct {
    int i;
    int j;
} Move;

void setValue(PLAYER **array, const int row, const int col, PLAYER value);
char getValue(PLAYER **array, const int row, const int col);
void initField(Field& field) ;
void deinitField(Field& field);
void plotLine(int sizeX);
void printField(Field& field);
bool isValid(Field& field, int x, int y);
bool isEmpty(Field& field, int x, int y);
void humanTurn(Field& field);
enum GameState checkWin(Field& field, PLAYER c);
bool aiTryBlock(Field& field);
bool gameCheck(Field& field, PLAYER dot, const std::string &winString);
int minimax (Field& field,bool maximazingFlag);
void getAiMove(Field& field);

#endif // FUNCTIONS_H
