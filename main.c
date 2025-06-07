/**
 * @author - Ian Yim
 */

#include <stdio.h>
#include <stdlib.h>

#define IS_WHITE(p) ((p) % 2 == 1)
#define IS_BLACK(p) ((p) % 2 == 0 && (p) != 0)

typedef uint64_t Bitboard;

// game_flags
#define WHITE_TURN       0x01
#define W_KING_MOVED     0x02
#define W_K_ROOK_MOVED   0x04
#define W_Q_ROOK_MOVED   0x08
#define B_KING_MOVED     0x10
#define B_K_ROOK_MOVED   0x20
#define B_Q_ROOK_MOVED   0x40

// move_flags
#define PROMOTE_QUEEN    0x01
#define PROMOTE_ROOK     0x02
#define PROMOTE_BISHOP   0x04
#define PROMOTE_KNIGHT   0x08
#define IS_EN_PASSANT    0x10
#define IS_CASTLE_KING   0x20
#define IS_CASTLE_QUEEN  0x40

typedef struct chess_board {
    unsigned char* boardArr; // size 64
    unsigned char game_flags; // hasKingRookMoved hasQueenRookMoved hasKingMoved isWhiteTurn
    unsigned char pawnJumps;
} chess_board;

typedef struct move_node {
    unsigned char from;
    unsigned char to;
    unsigned char move_flags; // Q-Promo B-P N-P R-P EnPassent Q-castle K-castle
    unsigned char pawnJumps;
    struct move_node* next;
} move_node;

// empty(0) pawn(1, 2) knight(3, 4) bishop(5, 6) rook(7, 8) queen(9, 10) king(11, 12)

move_node* newNode(unsigned char from, unsigned char to, unsigned char otherInfo, unsigned char pawnJumps) {
    move_node* new = malloc(sizeof(move_node));
    if(new == NULL) {
        fprintf(stderr, "Memory Allocation Error!");
        exit(1);
    }
    new->from = from;
    new->to = to;
    new->move_flags = otherInfo;
    new->pawnJumps = pawnJumps;
    return new;
}

chess_board* newBoard() {
    chess_board* new = malloc(sizeof(chess_board));
    if(new == NULL) {
        fprintf(stderr, "Memory Allocation Error!");
        exit(1);
    }
    new->boardArr = calloc(64, sizeof(unsigned char));
    if(new->boardArr == NULL) {
        fprintf(stderr, "Memory Allocation Error!");
        exit(1);
    }

    for(int i = 0; i < 8; ++i) {
        // Pawns
        new->boardArr[8 + i] = 2;
        new->boardArr[48 + i] = 1;
    }

    for(int i = 0; i < 2; ++i) {
        new->boardArr[0 + 56 * i] = 8 - i;      // Rook
        new->boardArr[1 + 56 * i] = 4 - i;      // Knight  
        new->boardArr[2 + 56 * i] = 6 - i;      // Bishop
        new->boardArr[3 + 56 * i] = 10 - i;     // Queen
        new->boardArr[4 + 56 * i] = 12 - i;     // King
        new->boardArr[5 + 56 * i] = 6 - i;      // Bishop
        new->boardArr[6 + 56 * i] = 4 - i;      // Knight
        new->boardArr[7 + 56 * i] = 8 - i;      // Rook
    }
    new->game_flags = WHITE_TURN;
    new->pawnJumps = 0;
    return new;
}

void printBoard(chess_board* b) {
    for(int i = 0; i < 8; ++i) {
        for(int j = 0; j < 8; ++j) {
            printf("%d ", b->boardArr[j + 8 * i]);
        }
        printf("\n");
    }
}

void append(move_node** hd, move_node* nd) {
    move_node* temp = *hd;
    *hd = nd;
    nd->next = temp;
}

void* addPossiblePawnMoves(chess_board* b, move_node** hd, int i, int j) {
    move_node* nd;
    unsigned char index = j + 8 * i;
    unsigned char isWhiteTurn = b->game_flags % 2;
    if(b->boardArr[index + (8 - 16 * isWhiteTurn)] == 0) {
        if(i == 6 - 5 * isWhiteTurn) {

        }
        else {
            nd = newNode(index, index + (8 - 16 * isWhiteTurn), 0, 0);
            append(hd, nd);
        }

        if((i == 1 + 5 * isWhiteTurn) && (b->boardArr[index + (16 - 32 * isWhiteTurn)] == 0)) {
            // double jump
            nd = newNode(index, index + (16 - 32 * isWhiteTurn), 0, 0x80 >> j);
            append(hd, nd);
        }
    }
}

move_node* possibleMoves(chess_board* b) {
    move_node *hd = NULL;
    move_node *temp, *nd;
    unsigned char wKingLoc, bKingLoc;
    unsigned char isWhiteTurn = b->game_flags % 2;
    for(int i = 0; i < 8; ++i) {
        for(int j = 0; j < 8; ++j) {
            unsigned char index = j + 8 * i;
            unsigned char piece = b->boardArr[index] + isWhiteTurn;
            if(piece == 2) {
                // Pawn
                addPossiblePawnMoves(b, &hd, i, j);
            }
            if(piece == 4) {
                // Knight
                char vectorX[8] = { -2, -1, 1, 2, 2, 1, -1, -2 };
                char vectorY[8] = { 1, 2, 2, 1, -1, -2, -2, -1 };
                for(int k = 0; k < 8; ++k) {
                    char x = j + vectorX[k];
                    char y = i + vectorY[k];
                    if(x < 0 || x > 7 || y < 0 || y > 7) {
                        continue;
                    }
                    unsigned char coordinate = x + 8 * y;
                    if(b->boardArr[coordinate] == 0 || b->boardArr[coordinate] % 2 != isWhiteTurn) {
                        nd = newNode(index, coordinate, 0, 0);
                        append(&hd, nd);
                    }
                }
            }
            if(piece == 12) {
                // King
            }

            if(piece == 6) {
                // Bishop
            }
            if(piece == 8) {
                // Rook
            }
            if(piece == 10) {
                // Queen
            }
        }
    }
    return hd;
}

int main() {
    printBoard(newBoard());

    return 0;
}