#include "util.h"
#include "move.h"

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
    *moveNum = 0; // 임시
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
