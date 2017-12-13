#include <stdio.h>
#include <stdlib.h>
#include "pieceConst.h"

extern int checkPosition(int row, int col, int b[][8]);

int attackedByPawn(int colPawn, int rowPawn, int colSquare, int rowSquare, int player);

int attackedByKnight(int colKnight, int rowKnight, int colSquare, int rowSquare);

int attackedByBishop(int colBishop, int rowBishop, int colSquare, int rowSquare, int player, int board[][8]);

int attackedByRook(int colRook, int rowRook, int colSquare, int rowSquare, int player, int board[][8]);

int attackedByQueen(int colQueen, int rowQueen, int colSquare, int rowSquare, int player, int board[][8]);

int attackedByKing(int colKing, int rowKing, int colSquare, int rowSquare);

int squareUnderAttack(int colPos, int rowPos, int player, int board[][8]) {
    /*TODO: a square-attacked checker function*/
    /* if player is white */
    /* return 1 if there has a piece attacked the square */
    if (!player) {
        int i, j;
        for (i = 0; i < 8; i++) {
            for (j = 0; j < 8; j++) {
                if (board[i][j] == bPawn) {
                    /* pawn */
                    if (attackedByPawn(j, i, colPos, rowPos, player)) {     // black's turn = 1;
                        return 1;
                    }
                } else if (board[i][j] == bKnight) {
                    /* knight */
                    if (attackedByKnight(j, i, colPos, rowPos)) {
                        return 1;
                    }
                } else if (board[i][j] == bBishop) {
                    /* bishop */
                    if (attackedByBishop(j, i, colPos, rowPos, player, board)) {
                        return 1;
                    }
                } else if (board[i][j] == bRook) {
                    /* rook */
                    if (attackedByRook(j, i, colPos, rowPos, player, board)) {
                        return 1;
                    }
                } else if (board[i][j] == bQueen) {
                    /* queen */
                    if (attackedByQueen(j, i, colPos, rowPos, player, board)) {
                        return 1;
                    }
                } else if (board[i][j] == bKing) {
                    /* king */
                    if (attackedByKing(j, i, colPos, rowPos)) {
                        return 1;
                    }
                }

            }
        }
    } else {
        /* if player is black */
        int i, j;
        for (i = 0; i < 8; i++) {
            for (j = 0; j < 8; j++) {
                if (board[i][j] == wPawn) {
                    /* pawn */
                    if (attackedByPawn(j, i, colPos, rowPos, player)) {     // white's turn = 0;
                        return 1;
                    }
                } else if (board[i][j] == wKnight) {
                    /* knight */
                    if (attackedByKnight(j, i, colPos, rowPos)) {
                        return 1;
                    }
                } else if (board[i][j] == wBishop) {
                    /* bishop */
                    if (attackedByBishop(j, i, colPos, rowPos, player, board)) {
                        return 1;
                    }
                } else if (board[i][j] == wRook) {
                    /* rook */
                    if (attackedByRook(j, i, colPos, rowPos, player, board)) {
                        return 1;
                    }
                } else if (board[i][j] == wQueen) {
                    /* queen */
                    if (attackedByQueen(j, i, colPos, rowPos, player, board)) {
                        return 1;
                    }
                } else if (board[i][j] == wKing) {
                    /* king */
                    if (attackedByKing(j, i, colPos, rowPos)) {
                        return 1;
                    }
                }

            }
        }
    }
    return 0;
}

/* must have player argument because movement of white pawn and black pawn is different */
int attackedByPawn(int colPawn, int rowPawn, int colSquare, int rowSquare, int player) {
    if (!player) {
        /* player is white, but checking the square control of black pawn */
        if (rowSquare == rowPawn + 1 && colSquare == colPawn + 1) {
            /*move south east*/
            return 1;
        } else if (rowSquare == rowPawn + 1 && colSquare == colPawn - 1) {
            /*move south west*/
            return 1;
        }
    } else {
        /* player is black, but checking the square control of white pawn */
        if (rowSquare == rowPawn - 1 && colSquare == colPawn + 1) {
            /*move north east*/
            return 1;
        } else if (rowSquare == rowPawn - 1 && colSquare == colPawn - 1) {
            /*move north west*/
            return 1;
        }
    }
    /* not attacked by pawn */
    return 0;
}

int attackedByKnight(int colKnight, int rowKnight, int colSquare, int rowSquare) {
    if (rowSquare == rowKnight + 1 && colSquare == colKnight + 2) {
        /*move 1 south 2 east*/
        return 1;
    } else if (rowSquare == rowKnight + 2 && colSquare == colKnight + 1) {
        /*move 2 south 1 east*/
        return 1;
    } else if (rowSquare == rowKnight + 2 && colSquare == colKnight - 1) {
        /*move 2 south 1 west*/
        return 1;
    } else if (rowSquare == rowKnight + 1 && colSquare == colKnight - 2) {
        /*move 1 south 2 west*/
        return 1;
    } else if (rowSquare == rowKnight - 1 && colSquare == colKnight - 2) {
        /*move 1 north 2 west*/
        return 1;
    } else if (rowSquare == rowKnight - 2 && colSquare == colKnight - 1) {
        /*move 2 north 1 west*/
        return 1;
    } else if (rowSquare == rowKnight - 2 && colSquare == colKnight + 1) {
        /*move 2 north 1 east*/
        return 1;
    } else if (rowSquare == rowKnight - 1 && colSquare == colKnight + 2) {
        /*move 1 north 2 east*/
        return 1;
    }
    /* not attacked by knight */
    return 0;
}

int attackedByBishop(int colBishop, int rowBishop, int colSquare, int rowSquare, int player, int board[][8]) {

    if (abs(colBishop - colSquare) == abs(rowBishop - rowSquare)) {
        /* bishop is taken by the king */
        if (colBishop - colSquare == 0) {
            return 0;
        }
        int i, j;

        if (rowSquare > rowBishop && colSquare > colBishop) {
            /*move south east*/
            i = rowBishop;
            for (j = colBishop + 1; j < colSquare; j++) {
                i++;
                if (checkPosition(i, j, board)) {
                    /*if piece at intermediate position, the square is not attacked*/
                    return 0;
                }
            }
        } else if (rowSquare > rowBishop && colSquare < colBishop) {
            /*move south west*/
            i = rowBishop;
            for (j = colBishop - 1; j > colSquare; j--) {
                i++;
                if (checkPosition(i, j, board)) {
                    /*if piece at intermediate position, the square is not attacked*/
                    return 0;
                }
            }
        } else if (rowSquare < rowBishop && colSquare < colBishop) {
            /*move north west*/
            i = rowBishop;
            for (j = colBishop - 1; j > colSquare; j--) {
                --i;
                if (checkPosition(i, j, board)) {
                    /*if piece at intermediate position, the square is not attacked*/
                    return 0;
                }
            }
        } else if (rowSquare < rowBishop && colSquare > colBishop) {
            /*move north east*/
            i = rowBishop;
            for (j = colBishop + 1; j < colSquare; j++) {
                --i;
                if (checkPosition(i, j, board)) {
                    /*if piece at intermediate position, the square is not attacked*/
                    return 0;
                }
            }
        }

        /* if there hasn't any piece at intermediate position, the square is attacked */
        return 1;
    }
    /* not attacked by bishop */
    return 0;
}

int attackedByRook(int colRook, int rowRook, int colSquare, int rowSquare, int player, int board[][8]) {

    int i;

    if (rowSquare > rowRook && colSquare == colRook) {
        /*move south*/
        for (i = rowRook + 1; i < rowSquare; ++i) {
            if (checkPosition(i, colRook, board)) {
                /*if piece at intermediate position, the square is not attacked*/
                return 0;
            }
        }
        /* if there hasn't any piece at intermediate position, the square is attacked */
        return 1;
    } else if (rowSquare == rowRook && colSquare < colRook) {
        /*move west*/
        for (i = colRook - 1; i > colSquare; --i) {
            if (checkPosition(rowRook, i, board)) {
                /*if piece at intermediate position, the square is not attacked*/
                return 0;
            }
        }
        /* if there hasn't any piece at intermediate position, the square is attacked */
        return 1;
    } else if (rowSquare < rowRook && colSquare == colRook) {
        /*move north*/
        for (i = rowRook - 1; i > rowSquare; --i) {
            if (checkPosition(i, colRook, board)) {
                /*if piece at intermediate position, the square is not attacked*/
                return 0;
            }
        }
        /* if there hasn't any piece at intermediate position, the square is attacked */
        return 1;
    } else if (rowSquare == rowRook && colSquare > colRook) {
        /*move east*/
        for (i = colRook + 1; i < colSquare; ++i) {
            if (checkPosition(rowRook, i, board)) {
                /*if piece at intermediate position, the square is not attacked*/
                return 0;
            }
        }
        /* if there hasn't any piece at intermediate position, the square is attacked */
        return 1;
    }

    /* not attacked by rook */
    return 0;
}

int attackedByQueen(int colQueen, int rowQueen, int colSquare, int rowSquare, int player, int board[][8]) {

	int i, j;
	/* look like bishop */
	if (abs(colQueen - colSquare) == abs(rowQueen - rowSquare)) {
        if (colQueen - colSquare == 0) {
            return 0;
        }
        if (rowSquare > rowQueen && colSquare > colQueen) {
            /*move south east*/
            i = rowQueen;
            for (j = colQueen + 1; j < colSquare; j++) {
                i++;
                if (checkPosition(i, j, board)) {
                    /*if piece at intermediate position, the square is not attacked*/
                    return 0;
                }
            }
        } else if (rowSquare > rowQueen && colSquare < colQueen) {
            /*move south west*/
            i = rowQueen;
            for (j = colQueen - 1; j > colSquare; j--) {
                i++;
                if (checkPosition(i, j, board)) {
                    /*if piece at intermediate position, the square is not attacked*/
                    return 0;
                }
            }
        } else if (rowSquare < rowQueen && colSquare < colQueen) {
            /*move north west*/
            i = rowQueen;
            for (j = colQueen - 1; j > colSquare; j--) {
                --i;
                if (checkPosition(i, j, board)) {
                    /*if piece at intermediate position, the square is not attacked*/
                    return 0;
                }
            }
        } else if (rowSquare < rowQueen && colSquare > colQueen) {
            /*move north east*/
            i = rowQueen;
            for (j = colQueen + 1; j < colSquare; j++) {
                --i;
                if (checkPosition(i, j, board)) {
                    /*if piece at intermediate position, the square is not attacked*/
                    return 0;
                }
            }
        }
        /* if there hasn't any piece at intermediate position, the square is attacked */
        return 1;
    }

    /* look like rook */
    if (rowSquare > rowQueen && colSquare == colQueen) {
        /*move south*/
        for (i = rowQueen + 1; i < rowSquare; ++i) {
            if (checkPosition(i, colQueen, board)) {
                /*if piece at intermediate position, the square is not attacked*/
                return 0;
            }
        }
        /* if there hasn't any piece at intermediate position, the square is attacked */
        return 1;
    } else if (rowSquare == rowQueen && colSquare < colQueen) {
        /*move west*/
        for (i = colQueen - 1; i > colSquare; --i) {
            if (checkPosition(rowQueen, i, board)) {
                /*if piece at intermediate position, the square is not attacked*/
                return 0;
            }
        }
        /* if there hasn't any piece at intermediate position, the square is attacked */
        return 1;
    } else if (rowSquare < rowQueen && colSquare == colQueen) {
        /*move north*/
        for (i = rowQueen - 1; i > rowSquare; --i) {
            if (checkPosition(i, colQueen, board)) {
                /*if piece at intermediate position, the square is not attacked*/
                return 0;
            }
        }
        /* if there hasn't any piece at intermediate position, the square is attacked */
        return 1;
    } else if (rowSquare == rowQueen && colSquare > colQueen) {
        /*move east*/
        for (i = colQueen + 1; i < colSquare; ++i) {
            if (checkPosition(rowQueen, i, board)) {
                /*if piece at intermediate position, the square is not attacked*/
                return 0;
            }
        }
        /* if there hasn't any piece at intermediate position, the square is attacked */
        return 1;
    }
    /* not attacked by queen */
    return 0;
}

int attackedByKing(int colKing, int rowKing, int colSquare, int rowSquare) {
    if (rowSquare == rowKing + 1 && colSquare == colKing) {
        /*move south*/
        return 1;
    } else if (rowSquare == rowKing && colSquare == colKing - 1) {
        /*move west*/
        return 1;
    } else if (rowSquare == rowKing - 1 && colSquare == colKing) {
        /*move north*/
        return 1;
    } else if (rowSquare == rowKing && colSquare == colKing + 1) {
        /*move east*/
        return 1;
    } else if (rowSquare == rowKing + 1 && colSquare == colKing + 1) {
        /*move south east*/
        return 1;
    } else if (rowSquare == rowKing + 1 && colSquare == colKing - 1) {
        /*move south west*/
        return 1;
    } else if (rowSquare == rowKing - 1 && colSquare == colKing - 1) {
        /*move north west*/
        return 1;
    } else if (rowSquare == rowKing - 1 && colSquare == colKing + 1) {
        /*move north east*/
        return 1;
    }
    /* not attacked by king */
    return 0;
}