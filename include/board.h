#ifndef BOARD_H
#define BOARD_H

#include <stdint.h>

#define IDX_empty 0
#define IDX_white 1
#define IDX_black 2
#define IDX_P 3
#define IDX_N 4
#define IDX_B 5
#define IDX_R 6
#define IDX_Q 7
#define IDX_K 8
#define IDX_p 9
#define IDX_n 10
#define IDX_b 11
#define IDX_r 12
#define IDX_q 13
#define IDX_k 14
#define IDX_metadataB 15

#define FLAG_WK_CASTLE 0x0100000000ULL
#define FLAG_WQ_CASTLE 0x0200000000ULL
#define FLAG_BK_CASTLE 0x0400000000ULL
#define FLAG_BQ_CASTLE 0x0800000000ULL
#define FLAG_W_TURN    0x1000000000ULL
#define MASK_EN_PASSANT 0x3ULL

typedef struct {
    uint64_t board[16];
} chess_board;

void initializeBoard(chess_board *board);

#endif