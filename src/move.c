#include "util.h"
#include "move.h"

void doMove(chess_board *board, move *move) {
    uint64_t* boardArr = board->board;
    const uint64_t metadataB = boardArr[IDX_metadataB];
    const uint64_t metadataM = move->metadataM;
    boardArr[IDX_metadataB] = (metadataB & ~MASK_EN_PASSANT_AND_CASTLE) | (metadataM & MASK_EN_PASSANT_AND_CASTLE);
    
    const uint64_t white_turn = -!!(metadataB & FLAG_W_TURN);
    const uint64_t black_turn = ~white_turn;
    const uint64_t to         = move->to;
    const uint64_t from       = move->from;

    if(metadataM & (DO_EN_PASSANT | DO_WK_CASTLE | DO_WQ_CASTLE | DO_BK_CASTLE | DO_BQ_CASTLE)) {
        const uint64_t is_enpassant  = -!!(metadataM & DO_EN_PASSANT); 
        const uint64_t black_capture = to << 8;
        const uint64_t white_capture = to >> 8;
        const uint64_t wk_castle = -!!(metadataM & DO_WK_CASTLE);
        const uint64_t wq_castle = -!!(metadataM & DO_WQ_CASTLE);
        const uint64_t bk_castle = -!!(metadataM & DO_BK_CASTLE);
        const uint64_t bq_castle = -!!(metadataM & DO_BQ_CASTLE);
        const uint64_t w_castle  = wk_castle | wq_castle;
        const uint64_t b_castle  = bk_castle | bq_castle;

        const uint64_t board_P = boardArr[IDX_P];
        const uint64_t board_p = boardArr[IDX_p];
        const uint64_t board_K = boardArr[IDX_K];
        const uint64_t board_k = boardArr[IDX_k];
        const uint64_t board_R = boardArr[IDX_R];
        const uint64_t board_r = boardArr[IDX_r];
        const uint64_t board_empty = boardArr[IDX_empty];
        const uint64_t board_white = boardArr[IDX_white];
        const uint64_t board_black = boardArr[IDX_black];

        boardArr[IDX_P] = (((((board_P & ~from) | to) & white_turn) | (board_P & ~black_capture & black_turn)) & is_enpassant) | (board_P & ~is_enpassant);
        boardArr[IDX_p] = (((((board_p & ~from) | to) & black_turn) | (board_p & ~white_capture & white_turn)) & is_enpassant) | (board_p & ~is_enpassant);        

        boardArr[IDX_K] = (board_K & ~e1 & w_castle) | (g1 & wk_castle) | (c1 & wq_castle) | (board_K & ~w_castle);
        boardArr[IDX_k] = (board_k & ~e8 & b_castle) | (g8 & bk_castle) | (c8 & bq_castle) | (board_k & ~b_castle);
        boardArr[IDX_R] = (board_R & ((~h1 & wk_castle) | (~a1 & wq_castle) | ~w_castle)) | (f1 & wk_castle) | (d1 & wq_castle);
        boardArr[IDX_r] = (board_r & ((~h8 & bk_castle) | (~a8 & bq_castle) | ~b_castle)) | (f8 & bk_castle) | (d8 & bq_castle);    
        
        const uint64_t w_castle_empty = ((board_empty & ~(g1 | f1)) | (e1 | h1) & wk_castle) | ((board_empty & ~(c1 | d1)) | (e1 | a1) & wq_castle);
        const uint64_t b_castle_empty = ((board_empty & ~(g8 | f8)) | (e8 | h8) & bk_castle) | ((board_empty & ~(c8 | d8)) | (e8 | a8) & bq_castle);

        const uint64_t w_castle_white = ((board_white & ~(e1 | h1)) | (g1 | f1) & wk_castle) | ((board_white & ~(e1 | a1)) | (c1 | d1) & wq_castle);
        const uint64_t b_castle_black = ((board_black & ~(e8 | h8)) | (g8 | f8) & bk_castle) | ((board_black & ~(e8 | a8)) | (c8 | d8) & bq_castle);
        
        boardArr[IDX_empty] = ((board_empty & ~to) | from | (white_capture & white_turn) | (black_capture & black_turn) & is_enpassant) | w_castle_empty | b_castle_empty;
        boardArr[IDX_white] = (((((board_white & ~from) | to) & white_turn) | (board_white & ~black_capture & black_turn)) & is_enpassant) | w_castle_white;
        boardArr[IDX_black] = (((((board_black & ~from) | to) & black_turn) | (board_black & ~white_capture & white_turn)) & is_enpassant) | b_castle_black;
    } else {
        boardArr[(metadataM & MASK_TAKE) >> SHIFT_TAKE] &= ~to;
        boardArr[(metadataM & MASK_FROM) >> SHIFT_FROM] &= ~from;
        boardArr[IDX_empty] |= from;
        boardArr[(metadataM & MASK_TO) >> SHIFT_TO] |= to;
        boardArr[IDX_white] = (((boardArr[IDX_white] & ~from) | to) & white_turn) | (boardArr[IDX_white] & ~(to & -!!(metadataM & MASK_TAKE)) & black_turn);
        boardArr[IDX_black] = (((boardArr[IDX_black] & ~from) | to) & black_turn) | (boardArr[IDX_black] & ~(to & -!!(metadataM & MASK_TAKE)) & white_turn);
    }

    boardArr[IDX_metadataB] ^= FLAG_W_TURN;
}

void generateMove(chess_board *board, move *moveList, int *moveNum) {
    /*
    int num = 0;
    int piece = n;
    if(boardArr[metadataC] & WHITE_TURN) {
        piece -= 6;
    }
    if(boardArr[piece] & 0x00007F7F7F7F7F7FULL) {
        
    }
    *moveNum = num;
    */
}
