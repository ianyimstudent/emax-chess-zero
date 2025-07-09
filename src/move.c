#include "util.h"
#include "move.h"

void doMove(chess_board *board, move *move) {
    board->board[IDX_metadataB] = (board->board[IDX_metadataB] & ~MASK_EN_PASSANT_AND_CASTLE) | (move->metadataM & MASK_EN_PASSANT_AND_CASTLE);
    
    if(move->metadataM & DO_WK_CASTLE) {
        board->board[IDX_K] = (board->board[IDX_K] & ~0x8ULL) | 0x2ULL;
        board->board[IDX_R] = (board->board[IDX_R] & ~0x1ULL) | 0x4ULL;
        board->board[IDX_empty] = (board->board[IDX_empty] & ~0x6ULL) | 0x9ULL;
        board->board[IDX_white] = (board->board[IDX_white] & ~0x9ULL) | 0x6ULL;
    } else if(move->metadataM & DO_WQ_CASTLE) {
        board->board[IDX_K] = (board->board[IDX_K] & ~0x8ULL) | 0x20ULL;
        board->board[IDX_R] = (board->board[IDX_R] & ~0x80ULL) | 0x10ULL;
        board->board[IDX_empty] = (board->board[IDX_empty] & ~0x30ULL) | 0x81ULL;
        board->board[IDX_white] = (board->board[IDX_white] & ~0x81ULL) | 0x30ULL;
    } else if(move->metadataM & DO_BK_CASTLE) {
        board->board[IDX_k] = (board->board[IDX_k] & ~0x0800000000000000ULL) | 0x0200000000000000ULL;
        board->board[IDX_r] = (board->board[IDX_r] & ~0x0100000000000000ULL) | 0x0400000000000000ULL;
        board->board[IDX_empty] = (board->board[IDX_empty] & ~0x0600000000000000ULL) | 0x0900000000000000ULL;
        board->board[IDX_black] = (board->board[IDX_black] & ~0x0900000000000000ULL) | 0x0600000000000000ULL;
    } else if(move->metadataM & DO_BQ_CASTLE) {
        board->board[IDX_k] = (board->board[IDX_k] & ~0x0800000000000000ULL) | 0x2000000000000000ULL;
        board->board[IDX_r] = (board->board[IDX_r] & ~0x8000000000000000ULL) | 0x1000000000000000ULL;
        board->board[IDX_empty] = (board->board[IDX_empty] & ~0x3000000000000000ULL) | 0x8100000000000000ULL;
        board->board[IDX_black] = (board->board[IDX_black] & ~0x8100000000000000ULL) | 0x3000000000000000ULL;
    } else if(move->metadataM & DO_EN_PASSANT) {
        if(board->board[IDX_metadataB] & FLAG_W_TURN) {
            board->board[IDX_empty] = (board->board[IDX_empty] & ~(move->to)) | move->from | (move->to >> 8); 
            board->board[IDX_P] = (board->board[IDX_P] & ~(move->from)) | move->to;
            board->board[IDX_p] &= ~(move->to >> 8);
            board->board[IDX_white] = (board->board[IDX_white] & ~(move->from)) | move->to;
            board->board[IDX_black] &= ~(move->to >> 8);
        } else {
            board->board[IDX_empty] = (board->board[IDX_empty] & ~(move->to)) | move->from | (move->to << 8); 
            board->board[IDX_p] = (board->board[IDX_p] & ~(move->from)) | move->to;
            board->board[IDX_P] &= ~(move->to << 8);
            board->board[IDX_black] = (board->board[IDX_black] & ~(move->from)) | move->to;
            board->board[IDX_white] &= ~(move->to << 8);
        }
    } else {
        board->board[(move->metadataM & MASK_TAKE) >> SHIFT_TAKE] &= ~(move->to);
        board->board[(move->metadataM & MASK_FROM) >> SHIFT_FROM] &= ~(move->from);
        board->board[IDX_empty] |= move->from;
        board->board[(move->metadataM & MASK_TO) >> SHIFT_TO] |= move->to;
        if(board->board[IDX_metadataB] & FLAG_W_TURN) {
            board->board[IDX_white] = (board->board[IDX_white] & ~move->from) | move->to;
            board->board[IDX_black] &= ~(move->to & -!!(move->metadataM & MASK_TAKE));
        } else {
            board->board[IDX_black] = (board->board[IDX_black] & ~move->from) | move->to;
            board->board[IDX_white] &= ~(move->to & -!!(move->metadataM & MASK_TAKE));
        }
    }

    board->board[IDX_metadataB] ^= FLAG_W_TURN;
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
