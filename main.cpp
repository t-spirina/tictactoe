#include <algorithm>
#include "functions.h"

int main() { // 1TBS
    //game cycle
    Field f;
    while (true) {
        initField(f);
        printField(f);
        while (true) {
            humanTurn(f);
            if (gameCheck(f, HUMAN, "ВЫ ПОБЕДИЛИ")) break;
            //aiTurn(f);
            getAiMove(f);
            if (gameCheck(f, AI, "ПОБЕДИЛ КОМПЬЮТЕР")) break;
        }
        deinitField(f);
        std::string answer;
        std::cout << "СЫГРАТЬ ЕЩЕ РАЗ? ";
        std::cin >> answer;
        // y, yes, yep, yay, yeah
        transform(answer.begin(), answer.end(), answer.begin(), ::tolower);
        if (answer.find('y') != 0) break;
    }

    return 0;
}
