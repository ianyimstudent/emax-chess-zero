#ifndef MOVE_H
#define MOVE_H

#include <stdint.h>
#include "board.h"

#define MASK_FROM   0x000F0000ULL
#define MASK_TO     0x00F00000ULL
#define MASK_TAKE   0x0F000000ULL
#define SHIFT_FROM  16
#define SHIFT_TO    20
#define SHIFT_TAKE  24

typedef struct {
    uint64_t from;
    uint64_t to;
    uint64_t metadataM;
    float score;
} move;

void doMove(chess_board *board, move *move);
void generateMove(chess_board *board, move *moveList, int *moveNum);

#endif