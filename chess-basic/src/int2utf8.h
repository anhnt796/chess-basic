/*takes a number 0-12 and converts it to unicode chess piece or blank square*/
#include "pieceConst.h"

char *convertClipieceToGuiPiece(int cliPiece) {
    if (cliPiece == wPawn) {
        return "♙";
    } else if (cliPiece == wKnight) {
        return "♘";
    } else if (cliPiece == wBishop) {
        return "♗";
    } else if (cliPiece == wRook) {
        return "♖";
    }
    else if (cliPiece == wQueen) {
        return "♕";
    }
    else if (cliPiece == wKing) {
        return "♔";
    } else if (cliPiece == bPawn) {
        return "♟";
    } else if (cliPiece == bKnight) {
        return "♞";
    } else if (cliPiece == bBishop) {
        return "♝";
    } else if (cliPiece == bRook) {
        return "♜";
    }
    else if (cliPiece == bQueen) {
        return "♛";
    }
    else if (cliPiece == bKing) {
        return "♚";
    } else {
        return "";
    }
}
