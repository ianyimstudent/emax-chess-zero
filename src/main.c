/**
 * @author - Ian Yim
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

// macro for chess_board index
#define empty 0
#define white 1
#define black 2
#define P 3
#define N 4
#define B 5
#define R 6
#define Q 7
#define K 8
#define p 9
#define n 10
#define b 11
#define r 12
#define q 13
#define k 14
#define metadataC 15

// macro for metadataC
#define W_K_CASTLE 0x0100ULL
#define W_Q_CASTLE 0x0200ULL
#define B_K_CASTLE 0x0400ULL
#define B_Q_CASTLE 0x0800ULL
#define WHITE_TURN 0x1000ULL

// macro for metadataM 
#define PROMOTED_Q 0x0100ULL
#define PROMOTED_R 0x0200ULL
#define PROMOTED_B 0x0400ULL
#define PROMOTED_N 0x0800ULL
#define EN_PASSANT 0x1000ULL
#define W_K_CASTLE 0x2000ULL

typedef struct chess_board {
    uint64_t board[16];
} chess_board;

typedef struct move {
    uint64_t from;
    uint64_t to;
    uint64_t metadataM;
    float score;
} move;

void doMove(chess_board *board, move *move) {
    board->board[move->metadataM & 0x00F0000] ^= move->from;
    board->board[move->metadataM & 0xF000000] ^= move->to;
    board->board[move->metadataM & 0x0F00000] |= move->to;
}

void generateMove(chess_board *board, move *moveList, int *moveNum) {
    int num = 0;
    int piece = n;
    if(board->board[metadataC] & WHITE_TURN) {
        piece -= 6;
    }
    if(board->board[piece] & 0x00007F7F7F7F7F7FULL) {
        
    }
    *moveNum = num;
}

void initializeBoard(chess_board *board) {
    board->board[empty] = 0x0000FFFFFFFF0000ULL;
    board->board[white] = 0x000000000000FFFFULL;
    board->board[black] = 0xFFFF000000000000ULL;
    board->board[P] = 0x000000000000FF00ULL;
    board->board[N] = 0x0000000000000042ULL;
    board->board[B] = 0x0000000000000024ULL;
    board->board[R] = 0x0000000000000081ULL;
    board->board[Q] = 0x0000000000000010ULL;
    board->board[K] = 0x0000000000000008ULL;
    board->board[p] = board->board[P] << 40;
    board->board[n] = board->board[N] << 56;
    board->board[b] = board->board[B] << 56;
    board->board[r] = board->board[R] << 56;
    board->board[q] = board->board[Q] << 56;
    board->board[k] = board->board[K] << 56;
    board->board[metadataC] = 0x0000000000001F00ULL;
}

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