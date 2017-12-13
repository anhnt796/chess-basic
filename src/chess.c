#include <stdio.h>
#include <string.h>
#include "pieceConst.h"

extern int rook(int pos[], int player, int board[][8]);

extern int knight(int pos[], int player, int board[][8]);

extern int bishop(int pos[], int player, int board[][8]);

extern int queen(int pos[], int player, int board[][8]);

extern int king(int pos[], int player, int board[][8]);

extern int pawn(int pos[], int player, int board[][8]);

extern int completemove(int pos[], int board[][8]);

extern void completecastlemove(int cases, int b[][8]);

extern int checkPosition(int row, int col, int b[][8]);

extern int squareUnderAttack(int colPos, int rowPos, int player, int board[][8]);
/*
struct wChessPieces {
	int type;
	struct wChessPieces next;
	struct wChessPieces prev;
}

struct bChessPieces {
	int type;
	struct bChessPieces next;
	struct bChessPieces prev;
}
*/
/*bChessPieces nodeB;
wChessPieces nodeW;
*/
/*int board[8][8]; for use with cmd chess*/

int enPassantW[8], enPassantB[8];
int castleW[2], castleB[2]; // index = 0: castle kingside, index = 1: castle queenside;

void initBoard(int tmpBoard[][8]) {
    tmpBoard[7][7] = wRook;
    tmpBoard[7][6] = wKnight;
    tmpBoard[7][5] = wBishop;
    tmpBoard[7][3] = wQueen;
    tmpBoard[7][4] = wKing;
    tmpBoard[7][2] = wBishop;
    tmpBoard[7][1] = wKnight;
    tmpBoard[7][0] = wRook;
    tmpBoard[0][7] = bRook;
    tmpBoard[0][6] = bKnight;
    tmpBoard[0][5] = bBishop;
    tmpBoard[0][3] = bQueen;
    tmpBoard[0][4] = bKing;
    tmpBoard[0][2] = bBishop;
    tmpBoard[0][1] = bKnight;
    tmpBoard[0][0] = bRook;

    int i, j;
    for (j = 0; j < 8; ++j) {
        /*black row of pawns*/
        tmpBoard[1][j] = bPawn;
    }

    for (j = 0; j < 8; ++j) {
        /*white row of pawns*/
        tmpBoard[6][j] = wPawn;
    }

    for (i = 2; i < 6; ++i) {
        for (j = 0; j < 8; ++j) {
            /*setup empty squares*/
            tmpBoard[i][j] = emptySquare;
        }
    }

    for (i = 0; i < 2; i++) {
        castleW[i] = 1;     // white can castle kside and qside
        castleB[i] = 1;     // black can castle kside and qside
    }
}

/*set the en passant arrays to 0
* this should be called whenever a move
* is made, except if a pawn is moved two
* squares */
void resetPassantArrays(void) {
    int i;
    for (i = 0; i < 8; ++i) {
        enPassantW[i] = 0;
        enPassantB[i] = 0;
    }
}

/*call this procedure when a king/rook movement is made*/
void setCastle(int cases) {
    switch (cases) {
        case 0: castleW[0] = 0; break;
        case 1: castleW[1] = 0; break;
        case 2: castleB[0] = 0; break;
        case 3: castleB[1] = 0; break;
        default: break;
    }
}

/*set the a index of the enPassantArray
* the first parameter is the index,
* it corresponds to a column on the board.
* The second is the player color 0 = white
* 1 = black.*/
void setPassant(int column, int player) {
    if (player) {
        enPassantB[column] = 1;
    } else {
        enPassantW[column] = 1;
    }
}

/* check if en passant jumped over the position last round.
* Check the opposite color of the current player
* Pawn must be on its fifth rank*/
int checkPassant(int row, int column, int player) {
    if (!player) {
        if (row == 3) {
            return enPassantB[column];
        } else return 0;
    } else {
        if (row == 4) {
            return enPassantW[column];
        } else return 0;
    }
}


int checkColor(int move[], int player, int b[][8]) {
    /*[0] = curCol, [1] curRow, [2] nexCol, [3] nexRow*/
    int colA = move[0];
    int colB = move[2];
    int aPiece = b[move[1]][colA];
    int dPiece = b[move[3]][colB];
    if (((player == 0) && ((aPiece > 0 && aPiece < 7) && ((dPiece > 6 && dPiece < 13) || (dPiece == 0)))) ||
        ((player == 1) && ((aPiece > 6 && aPiece < 13) && ((dPiece > 0 && dPiece < 7) || (dPiece == 0))))) {
        /* player is white and attacking piece is white, and defending piece is black or empty*/
        /* or player is black and attacking piece is black, and defending piece is white or empty*/
        return 1;
    } else {
        return 0;
    }
}

int checkMove(int input[], int player, int board[][8]) {
    /*convert char to int*/
    /*get the piece at the given coordinate*/
    int piece = board[input[1]][input[0]];
    /*hack for making 2 step pawn work*/
    int tmp;
    if (piece == 1 || piece == 7) {
        /*piece is a pawn*/
        tmp = pawn(input, player, board);
        if (tmp == 1) {
            /*The move is also made if pawn() returns 2*/
            /*some extraprocessing is needed and therfore pawn makes the move itself*/
            /*This is because of how pawn always called complete before*/
            completemove(input, board);
            /*move completed*/
            return 1;
        } else if (tmp == 2) {
            /*two step move*/
            return 1;
        } else {
            /*invalid move*/
            return 0;
        }
    } else if (piece == 2 || piece == 8) {
        /*piece is a knight*/
        if (knight(input, player, board)) {
            completemove(input, board);
            /*move completed*/
            return 1;
        } else {
            /*invalid move*/
            return 0;
        }
    } else if (piece == 3 || piece == 9) {
        /*piece is a bishop*/
        if (bishop(input, player, board)) {
            completemove(input, board);
            /*move completed*/
            return 1;
        } else {
            /*invalid move*/
            return 0;
        }
    } else if (piece == 4 || piece == 10) {
        /*piece is a rook*/
        if (rook(input, player, board)) {
            /*set castle when rook moved*/
            /*if player is white*/
            if (!player) {
                if (input[0] == 7 && input[1] == 7) {   // rook at h1
                    setCastle(WKSIDE);
                } else if (input[0] == 0 && input[1] == 7) {    // rook at a1
                    setCastle(WQSIDE);
                }
            }
            /*player is black*/
            else {
                if (input[0] == 7 && input[1] == 0) {   // rook at h8
                    setCastle(WKSIDE);
                } else if (input[0] == 0 && input[1] == 0) {    // rook at a8
                    setCastle(WQSIDE);
                }
            }
            completemove(input, board);
            /*move completed*/
            return 1;
        } else {
            /*invalid move*/
            return 0;
        }
    } else if (piece == 5 || piece == 11) {
        /*piece is a queen*/
        if (queen(input, player, board)) {
            completemove(input, board);
            /*move completed*/
            return 1;
        } else {
            /*invalid move*/
            return 0;
        }
    } else if (piece == 6 || piece == 12) {
        /*piece is a king*/
        /*check castle first*/
        /*white castle kingside*/
        if (player == WHITE && input[0] == 4 && input[1] == 7 && input[2] == 6 && input[3] == 7) {
            if (castleW[0]) {   // not castle yet
                if (checkPosition(7, 7, board) != wRook)    // there hasn't a rook on h1
                    return 0;
                if (checkPosition(7, 5, board))     // there has a piece on f1
                    return 0;
                if (checkPosition(7, 6, board))     // there has a piece on g1
                    return 0;
                if (squareUnderAttack(4, 7, WHITE, board))  // e1 is checked
                    return 0;
                if (squareUnderAttack(5, 7, WHITE, board))  // f1 is checked
                    return 0;
                if (squareUnderAttack(6, 7, WHITE, board))  // g1 is checked
                    return 0;
                completecastlemove(WKSIDE, board);
                setCastle(WKSIDE);
                setCastle(WQSIDE);
                return 1;
            } else {
                /*invalid castle*/
                return 0;
            }
        }
        /*white castle queenside*/
        else if (player == WHITE && input[0] == 4 && input[1] == 7 && input[2] == 2 && input[3] == 7) {
            if (castleW[1]) {
                if (checkPosition(7, 0, board) != wRook)    // there hasn't a rook on a1
                    return 0;
                if (checkPosition(7, 3, board))     // there has a piece on d1
                    return 0;
                if (checkPosition(7, 2, board))     // there has a piece on c1
                    return 0;
                if (checkPosition(7, 1, board))     // there has a piece on b1
                    return 0;
                if (squareUnderAttack(4, 7, WHITE, board))  // e1 is checked
                    return 0;
                if (squareUnderAttack(3, 7, WHITE, board))  // d1 is checked
                    return 0;
                if (squareUnderAttack(2, 7, WHITE, board))  // c1 is checked
                    return 0;
                completecastlemove(WQSIDE, board);
                setCastle(WKSIDE);
                setCastle(WQSIDE);
                return 1;
            } else {
                /*invalid castle*/
                return 0;
            }
        }
        /*black castle kingside*/
        else if (player == BLACK && input[0] == 4 && input[1] == 0 && input[2] == 6 && input[3] == 0) {
            if (castleB[0]) {
                if (checkPosition(0, 7, board) != bRook)    // there hasn't a rook on h8
                    return 0;
                if (checkPosition(0, 5, board))     // there has a piece on f8
                    return 0;
                if (checkPosition(0, 6, board))     // there has a piece on g8
                    return 0;
                if (squareUnderAttack(4, 0, BLACK, board))  // e8 is checked
                    return 0;
                if (squareUnderAttack(5, 0, BLACK, board))  // f8 is checked
                    return 0;
                if (squareUnderAttack(6, 0, BLACK, board))  // g8 is checked
                    return 0;
                completecastlemove(BKSIDE, board);
                setCastle(BKSIDE);
                setCastle(BQSIDE);
                return 1;
            } else {
                /*invalid castle*/
                return 0;
            }
        }
        /*black castle queenside*/
        else if (player == BLACK && input[0] == 4 && input[1] == 0 && input[2] == 2 && input[3] == 0) {
            if (castleB[1]) {
                if (checkPosition(0, 0, board) != bRook)    // there hasn't a rook on a8
                    return 0;
                if (checkPosition(0, 3, board))     // there has a piece on d8
                    return 0;
                if (checkPosition(0, 2, board))     // there has a piece on c8
                    return 0;
                if (checkPosition(0, 1, board))     // there has a piece on b8
                    return 0;
                if (squareUnderAttack(4, 0, BLACK, board))  // e8 is checked
                    return 0;
                if (squareUnderAttack(3, 0, BLACK, board))  // d8 is checked
                    return 0;
                if (squareUnderAttack(2, 0, BLACK, board))  // c8 is checked
                    return 0;
                completecastlemove(BQSIDE, board);
                setCastle(BKSIDE);
                setCastle(BQSIDE);
                return 1;
            } else {
                /*invalid castle*/
                return 0;
            }
        }
        /*normal move*/
        else if (king(input, player, board)) {
            printf("%d %d %d %d %d\n", input[0], input[1], input[2], input[3], player);
            completemove(input, board);
            /*move completed*/
            if (!player) {
                setCastle(WKSIDE);
                setCastle(WQSIDE);
            } else {
                setCastle(BKSIDE);
                setCastle(BQSIDE);
            }
            return 1;
        } else {
            /*invalid move*/
            return 0;
        }
    }
    /* invalid move */
    return 0;
}

int checkInput(int input[]) {
    /*check if the input is coordinates on board*/
    if ((input[0] >= 0 && input[0] < 8)) {
        /*check if first input is a letter A-H or a-h*/
        if (input[1] >= 0 && input[1] < 8) {
            /*check if second input is a number 1-8*/
            if ((input[2] >= 0 && input[2] < 8)) {
                /*check if third input is a letter A-H or a-h*/
                if (input[3] >= 0 && input[3] < 8) {
                    /*check if fourth input is a number 1-8*/
                    return 1;
                }
            }
        }
    }
    return 0;
}

int makemove(int player, int *move, int board[][8]) {
    if (checkInput(move)) {
        if (checkColor(move, player, board)) {
            if (checkMove(move, player, board)) {
                return 0;
            }
        }
    }
    return 1;
}
