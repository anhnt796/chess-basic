#include "pieceConst.h"

extern void resetPassantArrays();

/*
 This method will move a piece from its
 current position to a new one
*/
void completemove(int pos[], int b[][8]) {
    /*[0] = curCol, [1] curRow, [2] nexCol, [3] nexRow*/

    int tempPiece = b[pos[1]][pos[0]];
    b[pos[1]][pos[0]] = 0;
    b[pos[3]][pos[2]] = tempPiece;
    if (tempPiece == wPawn) {
    	if (pos[3] == 0) b[pos[3]][pos[2]] = wQueen;
    } else if (tempPiece == bPawn) {
    	if (pos[3] == 7) b[pos[3]][pos[2]] = bQueen;
    }
    resetPassantArrays();
}
