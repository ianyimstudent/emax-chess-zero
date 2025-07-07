/**
 * @author - Ian Yim
 */

#include "util.h"
#include "board.h"
#include "move.h"

int main() {
    chess_board board;
    move moveList[512];
    int moveNum = 0;

    initializeBoard(&board);
    generateMove(&board, moveList, &moveNum);
    for(int i = 0; i < moveNum; ++i) {
        doMove(&board, moveList + i);
    }

    return 0;
}