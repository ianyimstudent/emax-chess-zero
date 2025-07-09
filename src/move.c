#include "util.h"
#include "move.h"

void doMove(chess_board *board, move *move) {
    board->board[IDX_metadataB] = (board->board[IDX_metadataB] & ~MASK_EN_PASSANT_AND_CASTLE) | (move->metadataM & MASK_EN_PASSANT_AND_CASTLE);
    board->board[(move->metadataM & MASK_TAKE) >> SHIFT_TAKE] &= ~(move->to);
    board->board[(move->metadataM & MASK_FROM) >> SHIFT_FROM] &= ~(move->from);
    board->board[IDX_empty] |= move->from;
    board->board[(move->metadataM & MASK_TO) >> SHIFT_TO] |= move->to;

    if(unlikely(move->metadataM & DO_WK_CASTLE)) {
    
    } else if(unlikely(move->metadataM & DO_WQ_CASTLE)) {

    } else if(unlikely(move->metadataM & DO_BK_CASTLE)) {

    } else if(unlikely(move->metadataM & DO_BQ_CASTLE)) {

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
