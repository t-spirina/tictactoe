#include "functions.h"



void setValue(PLAYER **array, const int row, const int col, PLAYER value) {
    POINT_ITEM(array, row, col) = value;
}
char getValue(PLAYER **array, const int row, const int col) {
    return POINT_ITEM(array, row, col);
}
void initField(Field& field) {
    field.szX = 3;
    field.szY = 3;
    field.toWin = 3;
    field.map = (PLAYER**) calloc(field.szX, sizeof(PLAYER *));
    for (int y = 0; y < field.szY; y++) {
        *(field.map + y) = (PLAYER *) calloc(field.szX, sizeof(PLAYER));
        for (int x = 0; x < field.szX; x++) {
            setValue(field.map, y, x, EMPTY);
        }
    }
}
void deinitField(Field& field)
{
    std::free(field.map);
}
void plotLine(int sizeX)
{
    std::cout << std::endl<<"------";
    for (int x = 0; x < sizeX; x++)
        std::cout << "----" ;
    std::cout<< std::endl;
}
void printField(Field& field) {
    std::system("clear");

    std::cout << "     |";
    for (int x = 0; x < field.szX; x++)
        std::cout << " x"<<(x + 1) <<"|";
    plotLine(field.szX);
    for (int y = 0; y < field.szY; y++) {
        std::cout << "| y"<<(y + 1) <<" |";
        for (int x = 0; x < field.szX; x++) {
            std::cout << " " <<getValue(field.map, y, x) << " |";
        }
        plotLine(field.szX);
    }
}
bool isValid(Field& field, int x, int y) {
    return CHECK_DOT(x, field.szX) && CHECK_DOT(y, field.szY);
}
bool isEmpty(Field& field, int x, int y) {
    return getValue(field.map, y, x) == EMPTY;
}
void humanTurn(Field& field) {
    int x;
    int y;
    bool isError = false;
    do {
        if (isError)
            std::cout << "Поле ["<<x+1<<", "<<y+1<<"] занято" << std::endl;
        std::cout << "Введите координаты хода X и Y (от 1 до 3) через пробел >>" << std::endl;
        std::cin >> x;
        std::cin >> y;
        //<regex>
        x--; y--;
        isError = true;
    } while (!isValid(field, x, y) || !isEmpty(field, x, y));
    setValue(field.map, y, x, HUMAN);
}
bool checkLine(Field& field, int y, int x, int vx, int vy, int len) {
    const int endX = x + (len - 1) * vx;
    const int endY = y + (len - 1) * vy;
    char c = getValue(field.map, y, x);
    if (!isValid(field, endX, endY))
        return false;
    for (int i = 0; i < len; i++) {
        if (getValue(field.map, (y + i * vy), (x + i * vx)) != c)
            return false;
    }
    return true;
}
enum GameState checkWin(Field& field, PLAYER c) {
    bool hasEmpty = false;
    for (int y = 0; y < field.szY; y++) {
        for (int x = 0; x < field.szX; x++) {
            if (getValue(field.map, y, x) == EMPTY) {
                hasEmpty = true;
                continue;
            }
            if (getValue(field.map, y, x) != c) continue;
            if (checkLine(field, y, x, 1,  0, field.toWin)) return WIN;
            if (checkLine(field, y, x, 1,  1, field.toWin)) return WIN;
            if (checkLine(field, y, x, 0,  1, field.toWin)) return WIN;
            if (checkLine(field, y, x, 1, -1, field.toWin)) return WIN;
        }
    }
    return (hasEmpty) ? NOTWIN : DRAW;
}
bool aiTryWin(Field& field) {
    for (int y = 0; y < field.szY; y++) {
        for (int x = 0; x < field.szX; x++) {
            if (isEmpty(field, x, y)) {
                setValue(field.map, y, x, AI);
                if (checkWin(field, AI) == WIN)
                    return true;
                setValue(field.map, y, x, EMPTY);
            }
        }
    }
    return false;
}
bool aiTryBlock(Field& field) {
    for (int y = 0; y < field.szY; y++) {
        for (int x = 0; x < field.szX; x++) {
            if (isEmpty(field, x, y)) {
                setValue(field.map, y, x, HUMAN);
                if (checkWin(field, HUMAN) == WIN) {
                    setValue(field.map, y, x, AI);
                    return true;
                }
                setValue(field.map, y, x, EMPTY);
            }
        }
    }
    return false;
}


void aiTurn(Field& field) {

    if (aiTryWin(field)) return;
    if (aiTryBlock(field)) return;
    int x;
    int y;
    //C++11 <random>
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(0, (field.szX--));
    do {
        x = dist(mt);
        y = dist(mt);
    } while (!isEmpty(field, x, y));
    setValue(field.map, y, x, AI);
}
bool gameCheck(Field& field, PLAYER dot, const std::string &winString) {
    printField(field);
    enum GameState result = checkWin(field, dot);
    if (result == WIN) {
        std::cout << winString << std::endl;
        return true;
    } else if (result == DRAW) {
        std::cout << "НИЧЬЯ" << std::endl;
        return true;
    } else
        return false;
}
int minimax (Field& field,bool maximazingFlag)
{
    int score;
    PLAYER dot;
    int bestScore;
    //поиск закончится, когда будет победитель или ничья
    enum GameState gameResult=checkWin(field, AI);
    if( gameResult == WIN)
        return AIscore;
    else if (gameResult ==  DRAW)
        return DRAWscore;
    else if (checkWin(field, HUMAN)==WIN)
        return HUMANscore;
//ищем максимальное решение для х
    if(maximazingFlag){
        bestScore=(int)-INFINITY; //
        dot=HUMAN;
    }
//и минимальное для 0
    else{
        bestScore=(int)INFINITY;
        dot=AI;
    }
    for (int y = 0; y < field.szY; y++) {
        for (int x = 0; x < field.szX; x++) {
            if (isEmpty(field,x,y)){
                setValue(field.map, y, x, dot);
                score = minimax(field,(!maximazingFlag));//ход соперника
                setValue(field.map, y, x, EMPTY);
                if(maximazingFlag)
                    bestScore=GET_MAX(score,bestScore);// идельно, если 1 для х
                else
                    bestScore=GET_MIN(score,bestScore);// идеально, если -1 для 0
            }
        }
    }
    return bestScore;
}

void getAiMove(Field& field){
    int result =(int)-INFINITY;
    int bestMove=(int)INFINITY;
    int xMove, yMove;
    for (int y = 0; y < field.szY; y++) {
        for (int x = 0; x < field.szX; x++) {
            if (isEmpty(field,x,y))
            {
                //ищем пустую ячейку
                setValue(field.map, y, x, AI);
                //смотрим цену хода
                result = minimax(field,true);
                //ищем минимальное через минимакс, потому как ходит 0
               if (result < bestMove)
               {
                   xMove = x;
                   yMove = y;
                   bestMove = result;
                   //сохранаю первое из удачных решений
               }
               setValue(field.map, y, x, EMPTY);
            }
        }
    }
    setValue(field.map, yMove, xMove, AI);
}
