/**
 * @author - Ian Yim
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define likely(x)   __builtin_expect((x), 1)
#define unlikely(x) __builtin_expect((x), 0)

// macro for chess_board index
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

// macro for metadataB
#define FLAG_WK_CASTLE 0x0100000000ULL
#define FLAG_WQ_CASTLE 0x0200000000ULL
#define FLAG_BK_CASTLE 0x0400000000ULL
#define FLAG_BQ_CASTLE 0x0800000000ULL
#define FLAG_W_TURN 0x1000000000ULL

// macro for metadataM
#define MASK_FROM   0x000F0000ULL
#define MASK_TO     0x00F00000ULL
#define MASK_TAKE   0x0F000000ULL

#define SHIFT_FROM  16
#define SHIFT_TO    20
#define SHIFT_TAKE  24

// macro for both metadataB and metadataM
#define MASK_EN_PASSANT 0x3ULL

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
    board->board[IDX_metadataB] = (board->board[IDX_metadataB] & ~MASK_EN_PASSANT) | (move->metadataM & MASK_EN_PASSANT);   
    board->board[IDX_metadataB] ^= FLAG_W_TURN;

    board->board[(move->metadataM & MASK_FROM) >> SHIFT_FROM] &= ~(move->from);
    board->board[IDX_empty] |= move->from;
    board->board[(move->metadataM & MASK_TAKE) >> SHIFT_TAKE] &= ~(move->to);
    board->board[(move->metadataM & MASK_TO) >> SHIFT_TO] |= move->to;

    if(unlikely(move->metadataM & FLAG_WK_CASTLE)) {

    } else if(unlikely(move->metadataM & FLAG_WQ_CASTLE)) {
        
    } else if(unlikely(move->metadataM & FLAG_BK_CASTLE)) {
        
    } else if(unlikely(move->metadataM & FLAG_BQ_CASTLE)) {
        
    } else {
        
    }
}

void generateMove(chess_board *board, move *moveList, int *moveNum) {
    /*
    int num = 0;
    int piece = n;
    if(board->board[metadataC] & WHITE_TURN) {
        piece -= 6;
    }
    if(board->board[piece] & 0x00007F7F7F7F7F7FULL) {
        
    }
    *moveNum = num;
    */
}

void initializeBoard(chess_board *board) {
    /**
     * void initializeBoard(chess_board *board)
     *     -- Follows standard mapping
     *     - MSB (a1)
     *     - LSB (h8)
     */
    board->board[IDX_empty] = 0x0000FFFFFFFF0000ULL;
    board->board[IDX_white] = 0xFFFF000000000000ULL;
    board->board[IDX_black] = 0x000000000000FFFFULL;
    board->board[IDX_P] = 0x00FF000000000000ULL;
    board->board[IDX_N] = 0x4200000000000000ULL;
    board->board[IDX_B] = 0x2400000000000000ULL;
    board->board[IDX_R] = 0x8100000000000000ULL;
    board->board[IDX_Q] = 0x1000000000000000ULL;
    board->board[IDX_K] = 0x0800000000000000ULL;
    board->board[IDX_p] = board->board[IDX_P] >> 40;
    board->board[IDX_n] = board->board[IDX_N] >> 56;
    board->board[IDX_b] = board->board[IDX_B] >> 56;
    board->board[IDX_r] = board->board[IDX_R] >> 56;
    board->board[IDX_q] = board->board[IDX_Q] >> 56;
    board->board[IDX_k] = board->board[IDX_K] >> 56;
    board->board[IDX_metadataB] = FLAG_WK_CASTLE | FLAG_WQ_CASTLE | FLAG_BK_CASTLE | FLAG_BQ_CASTLE | FLAG_W_TURN;
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