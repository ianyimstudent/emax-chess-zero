#include "util.h"
#include "board.h"

void initializeBoard(chess_board *board) {
    /**
     * void initializeBoard(chess_board *board)
     *     -- Follows custom mapping
     *     - MSB (a8)
     *     - LSB (h1)
     *     a8, b8, ..., g1, h1  
     */

    board->board[IDX_empty] = 0x0000FFFFFFFF0000ULL;
    board->board[IDX_white] = 0x000000000000FFFFULL;
    board->board[IDX_black] = 0xFFFF000000000000ULL;
    board->board[IDX_P]     = 0x000000000000FF00ULL;
    board->board[IDX_N]     = 0x0000000000000042ULL;
    board->board[IDX_B]     = 0x0000000000000024ULL;
    board->board[IDX_R]     = 0x0000000000000081ULL;
    board->board[IDX_Q]     = 0x0000000000000010ULL;
    board->board[IDX_K]     = 0x0000000000000008ULL;
    board->board[IDX_p] = board->board[IDX_P] << 40;
    board->board[IDX_n] = board->board[IDX_N] << 56;
    board->board[IDX_b] = board->board[IDX_B] << 56;
    board->board[IDX_r] = board->board[IDX_R] << 56;
    board->board[IDX_q] = board->board[IDX_Q] << 56;
    board->board[IDX_k] = board->board[IDX_K] << 56;
    board->board[IDX_metadataB] = FLAG_WK_CASTLE | FLAG_WQ_CASTLE | FLAG_BK_CASTLE | FLAG_BQ_CASTLE | FLAG_W_TURN;
}
