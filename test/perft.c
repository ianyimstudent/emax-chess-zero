#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

#include "../include/board.h"
#include "../include/move.h"
#include "../include/timer.h"

uint64_t perft(chess_board *board, int depth) {
    if (depth == 0) return 1;

    move moveList[512];
    int moveNum = 0;
    generateMove(board, moveList, &moveNum);

    uint64_t nodes = 0;
    for (int i = 0; i < moveNum; ++i) {
        chess_board newBoard = *board;
        doMove(&newBoard, &moveList[i]);
        nodes += perft(&newBoard, depth - 1);
    }

    return nodes;
}

int main() {
    printf("Running perft test from initial position:\n\n");
    Timer t;
    chess_board board;
    initializeBoard(&board);

    for (int depth = 1; depth <= 5; ++depth) {
        timer_start(&t);
        uint64_t nodes = perft(&board, depth);
        uint64_t elapsed = timer_elapsed_ms(&t);

        printf("perft(%d) = %" PRIu64 " [%llu ms]\n", depth, nodes, elapsed);
    }
    return 0;
}
