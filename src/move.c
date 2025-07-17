#include "util.h"
#include "move.h"

void doMove(chess_board *board, move *move) {
    board->board[IDX_metadataB] = (board->board[IDX_metadataB] & ~MASK_EN_PASSANT_AND_CASTLE) | (move->metadataM & MASK_EN_PASSANT_AND_CASTLE);
    
    if(move->metadataM & DO_WK_CASTLE) {
        board->board[IDX_K] = (board->board[IDX_K] & ~e1) | g1;
        board->board[IDX_R] = (board->board[IDX_R] & ~h1) | f1;
        board->board[IDX_empty] = (board->board[IDX_empty] & ~(g1 | f1)) | (e1 | h1);
        board->board[IDX_white] = (board->board[IDX_white] & ~(e1 | h1)) | (g1 | f1);
    } else if(move->metadataM & DO_WQ_CASTLE) {
        board->board[IDX_K] = (board->board[IDX_K] & ~e1) | c1;
        board->board[IDX_R] = (board->board[IDX_R] & ~a1) | d1;
        board->board[IDX_empty] = (board->board[IDX_empty] & ~(c1 | d1)) | (e1 | a1);
        board->board[IDX_white] = (board->board[IDX_white] & ~(e1 | a1)) | (c1 | d1);
    } else if(move->metadataM & DO_BK_CASTLE) {
        board->board[IDX_k] = (board->board[IDX_k] & ~e8) | g8;
        board->board[IDX_r] = (board->board[IDX_r] & ~h8) | f8;
        board->board[IDX_empty] = (board->board[IDX_empty] & ~(g8 | f8)) | (e8 | h8);
        board->board[IDX_black] = (board->board[IDX_black] & ~(e8 | h8)) | (g8 | f8);
    } else if(move->metadataM & DO_BQ_CASTLE) {
        board->board[IDX_k] = (board->board[IDX_k] & ~e8) | c8;
        board->board[IDX_r] = (board->board[IDX_r] & ~a8) | d8;
        board->board[IDX_empty] = (board->board[IDX_empty] & ~(c8 | d8)) | (e8 | a8);
        board->board[IDX_black] = (board->board[IDX_black] & ~(e8 | a8)) | (c8 | d8);
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
