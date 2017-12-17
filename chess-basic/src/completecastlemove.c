#include "pieceConst.h"

extern void resetPassantArrays();

/*
 This method will move a castle move
*/
void completecastlemove(int cases, int b[][8]) {

    switch (cases) {
        case 0: 
            b[7][4] = 0;
            b[7][6] = wKing;
            b[7][7] = 0;
            b[7][5] = wRook;
            break;
        case 1:
            b[7][4] = 0;
            b[7][2] = wKing;
            b[7][0] = 0;
            b[7][3] = wRook;
            break;
        case 2:
            b[0][4] = 0;
            b[0][6] = bKing;
            b[0][7] = 0;
            b[0][5] = bRook;
            break;
        case 3:
            b[0][4] = 0;
            b[0][2] = bKing;
            b[0][0] = 0;
            b[0][3] = bRook;
            break;
    }
    
    resetPassantArrays();
}
