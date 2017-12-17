/* This function checks if the king is currently under attack
 * If the king is under attack, returns 1, else returns 0
 * Optional: returns 2 if double-checked.
 */
#include "pieceConst.h"

extern int squareUnderAttack(int colPos, int rowPos, int player, int board[][8]);

int kingUnderAttack(int player, int board[][8]) {
	
	int i, j, king, colKing, rowKing;
	king = player ? bKing : wKing;
	for (i = 0; i < 8; i++) {
		for (j = 0; j < 8; j++) {
			if (board[i][j] == king) {
				colKing = j;
				rowKing = i;
			}
		}
	}
	
	if (squareUnderAttack(colKing, rowKing, player, board)) {
		return 1;
	} else {
		return 0;
	}
}
