#include "pieceConst.h"

extern int rook(int pos[], int player, int board[][8]);

extern int knight(int pos[], int player, int board[][8]);

extern int bishop(int pos[], int player, int board[][8]);

extern int queen(int pos[], int player, int board[][8]);

extern int king(int pos[], int player, int board[][8]);

extern int pawn(int pos[], int player, int board[][8]);

extern int checkPosition(int row, int col, int b[][8]);

extern int makemove(int player, int *move, int board[][8]);

extern void returnCastleStatus(int status[]);

extern int castleW[2], castleB[2];

void returnTempBoard(int tempBoard[][8], int board[][8]);

int hasMovement(int player, int board[][8]) {
	/* board[row][col] */
	int i, j, piece;
	int pos[4];
	int tempBoard[8][8];
	int status[4];
	status[0] = castleW[0];
	status[1] = castleW[1];
	status[2] = castleB[0];
	status[3] = castleB[1];
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            tempBoard[i][j] = board[i][j];
        }
    }
	/*return 1 immediately if any piece has a legal movement*/
	if (!player) {
		/*player is white*/
		for (i = 7; i >= 0; i--) {
			for (j = 7; j >= 0; j--) {
				piece = checkPosition(i, j, tempBoard);
				pos[0] = j;	pos[1] = i;
				if (piece == wPawn) {
					pos[2] = j;		pos[3] = i + 2; if (!makemove(player, pos, tempBoard)) { returnTempBoard(tempBoard, board); return 1; }
					pos[2] = j;		pos[3] = i + 1; if (!makemove(player, pos, tempBoard)) { returnTempBoard(tempBoard, board); return 1; }
					pos[2] = j + 1; pos[3] = i + 1; if (!makemove(player, pos, tempBoard)) { returnTempBoard(tempBoard, board); return 1; }
					pos[2] = j - 1; pos[3] = i + 1; if (!makemove(player, pos, tempBoard)) { returnTempBoard(tempBoard, board); return 1; }
				} else if (piece == wKnight) {
					pos[2] = j + 1; pos[3] = i + 2; if (!makemove(player, pos, tempBoard)) { returnTempBoard(tempBoard, board); return 1; }
					pos[2] = j + 2; pos[3] = i + 1; if (!makemove(player, pos, tempBoard)) { returnTempBoard(tempBoard, board); return 1; }
					pos[2] = j + 1; pos[3] = i - 2; if (!makemove(player, pos, tempBoard)) { returnTempBoard(tempBoard, board); return 1; }
					pos[2] = j + 2; pos[3] = i - 1; if (!makemove(player, pos, tempBoard)) { returnTempBoard(tempBoard, board); return 1; }
					pos[2] = j - 1; pos[3] = i - 2; if (!makemove(player, pos, tempBoard)) { returnTempBoard(tempBoard, board); return 1; }
					pos[2] = j - 2; pos[3] = i - 1; if (!makemove(player, pos, tempBoard)) { returnTempBoard(tempBoard, board); return 1; }
					pos[2] = j - 1; pos[3] = i + 2; if (!makemove(player, pos, tempBoard)) { returnTempBoard(tempBoard, board); return 1; }
					pos[2] = j - 2; pos[3] = i + 1; if (!makemove(player, pos, tempBoard)) { returnTempBoard(tempBoard, board); return 1; }
				} else if (piece == wBishop) {
					pos[2] = j; pos[3] = i;
					while (pos[2] <= 7 && pos[3] >= 0) {
						if (!makemove(player, pos, tempBoard)) { returnTempBoard(tempBoard, board); return 1; }
						pos[2]++; pos[3]--;
					}
					pos[2] = j; pos[3] = i;
					while (pos[2] <= 7 && pos[3] <= 7) {
						if (!makemove(player, pos, tempBoard)) { returnTempBoard(tempBoard, board); return 1; }
						pos[2]++; pos[3]++;
					}
					pos[2] = j; pos[3] = i;
					while (pos[2] >= 0 && pos[3] >= 0) {
						if (!makemove(player, pos, tempBoard)) { returnTempBoard(tempBoard, board); return 1; }
						pos[2]--; pos[3]--;
					}
					pos[2] = j; pos[3] = i;
					while (pos[2] >= 0 && pos[3] <= 7) {
						if (!makemove(player, pos, tempBoard)) { returnTempBoard(tempBoard, board); return 1; }
						pos[2]--; pos[3]++;
					}
				} else if (piece == wRook) {
					pos[2] = j; pos[3] = i;
					while (pos[3] <= 7) {
						if (!makemove(player, pos, tempBoard)) { returnCastleStatus(status); returnTempBoard(tempBoard, board); return 1; }
						pos[3]++;
					}
					pos[2] = j; pos[3] = i;
					while (pos[3] >= 0) {
						if (!makemove(player, pos, tempBoard)) { returnCastleStatus(status); returnTempBoard(tempBoard, board); return 1; }
						pos[3]--;
					}
					pos[2] = j; pos[3] = i;
					while (pos[2] <= 7) {
						if (!makemove(player, pos, tempBoard)) { returnCastleStatus(status); returnTempBoard(tempBoard, board); return 1; }
						pos[2]++;
					}
					pos[2] = j; pos[3] = i;
					while (pos[2] >= 0) {
						if (!makemove(player, pos, tempBoard)) { returnCastleStatus(status); returnTempBoard(tempBoard, board); return 1; }
						pos[2]--;
					}
				} else if (piece == wQueen) {
					pos[2] = j; pos[3] = i;
					while (pos[2] <= 7 && pos[3] >= 0) {
						if (!makemove(player, pos, tempBoard)) { returnTempBoard(tempBoard, board); return 1; }
						pos[2]++; pos[3]--;
					}
					pos[2] = j; pos[3] = i;
					while (pos[2] <= 7 && pos[3] <= 7) {
						if (!makemove(player, pos, tempBoard)) { returnTempBoard(tempBoard, board); return 1; }
						pos[2]++; pos[3]++;
					}
					pos[2] = j; pos[3] = i;
					while (pos[2] >= 0 && pos[3] >= 0) {
						if (!makemove(player, pos, tempBoard)) { returnTempBoard(tempBoard, board); return 1; }
						pos[2]--; pos[3]--;
					}
					pos[2] = j; pos[3] = i;
					while (pos[2] >= 0 && pos[3] <= 7) {
						if (!makemove(player, pos, tempBoard)) { returnTempBoard(tempBoard, board); return 1; }
						pos[2]--; pos[3]++;
					}
					pos[2] = j; pos[3] = i;
					while (pos[3] <= 7) {
						if (!makemove(player, pos, tempBoard)) { returnTempBoard(tempBoard, board); return 1; }
						pos[3]++;
					}
					pos[2] = j; pos[3] = i;
					while (pos[3] >= 0) {
						if (!makemove(player, pos, tempBoard)) { returnTempBoard(tempBoard, board); return 1; }
						pos[3]--;
					}
					pos[2] = j; pos[3] = i;
					while (pos[2] <= 7) {
						if (!makemove(player, pos, tempBoard)) { returnTempBoard(tempBoard, board); return 1; }
						pos[2]++;
					}
					pos[2] = j; pos[3] = i;
					while (pos[2] >= 0) {
						if (!makemove(player, pos, tempBoard)) { returnTempBoard(tempBoard, board); return 1; }
						pos[2]--;
					}
				} else if (piece == wKing) {
					pos[2] = j + 1; pos[3] = i + 1; if (!makemove(player, pos, tempBoard)) { returnCastleStatus(status); returnTempBoard(tempBoard, board); return 1; }
					pos[2] = j + 1; pos[3] = i;		if (!makemove(player, pos, tempBoard)) { returnCastleStatus(status); returnTempBoard(tempBoard, board); return 1; }
					pos[2] = j + 1; pos[3] = i - 1; if (!makemove(player, pos, tempBoard)) { returnCastleStatus(status); returnTempBoard(tempBoard, board); return 1; }
					pos[2] = j;		pos[3] = i + 1; if (!makemove(player, pos, tempBoard)) { returnCastleStatus(status); returnTempBoard(tempBoard, board); return 1; }
					pos[2] = j;		pos[3] = i - 1; if (!makemove(player, pos, tempBoard)) { returnCastleStatus(status); returnTempBoard(tempBoard, board); return 1; }
					pos[2] = j - 1; pos[3] = i + 1; if (!makemove(player, pos, tempBoard)) { returnCastleStatus(status); returnTempBoard(tempBoard, board); return 1; }
					pos[2] = j - 1; pos[3] = i;		if (!makemove(player, pos, tempBoard)) { returnCastleStatus(status); returnTempBoard(tempBoard, board); return 1; }
					pos[2] = j - 1; pos[3] = i - 1; if (!makemove(player, pos, tempBoard)) { returnCastleStatus(status); returnTempBoard(tempBoard, board); return 1; }
				}
			}
		}
		return 0;
	} else {
		/* player is black */
		for (i = 0; i <= 7; i++) {
			for (j = 0; j <= 7; j++) {
				piece = checkPosition(i, j, tempBoard);
				pos[0] = j;	pos[1] = i;
				if (piece == bPawn) {
					pos[2] = j;		pos[3] = i - 2; if (!makemove(player, pos, tempBoard)) { returnTempBoard(tempBoard, board); return 1; }
					pos[2] = j;		pos[3] = i - 1; if (!makemove(player, pos, tempBoard)) { returnTempBoard(tempBoard, board); return 1; }
					pos[2] = j + 1; pos[3] = i - 1; if (!makemove(player, pos, tempBoard)) { returnTempBoard(tempBoard, board); return 1; }
					pos[2] = j - 1; pos[3] = i - 1; if (!makemove(player, pos, tempBoard)) { returnTempBoard(tempBoard, board); return 1; }
				} else if (piece == bKnight) {
					pos[2] = j + 1; pos[3] = i + 2; if (!makemove(player, pos, tempBoard)) { returnTempBoard(tempBoard, board); return 1; }
					pos[2] = j + 2; pos[3] = i + 1; if (!makemove(player, pos, tempBoard)) { returnTempBoard(tempBoard, board); return 1; }
					pos[2] = j + 1; pos[3] = i - 2; if (!makemove(player, pos, tempBoard)) { returnTempBoard(tempBoard, board); return 1; }
					pos[2] = j + 2; pos[3] = i - 1; if (!makemove(player, pos, tempBoard)) { returnTempBoard(tempBoard, board); return 1; }
					pos[2] = j - 1; pos[3] = i - 2; if (!makemove(player, pos, tempBoard)) { returnTempBoard(tempBoard, board); return 1; }
					pos[2] = j - 2; pos[3] = i - 1; if (!makemove(player, pos, tempBoard)) { returnTempBoard(tempBoard, board); return 1; }
					pos[2] = j - 1; pos[3] = i + 2; if (!makemove(player, pos, tempBoard)) { returnTempBoard(tempBoard, board); return 1; }
					pos[2] = j - 2; pos[3] = i + 1; if (!makemove(player, pos, tempBoard)) { returnTempBoard(tempBoard, board); return 1; }
				} else if (piece == bBishop) {
					pos[2] = j; pos[3] = i;
					while (pos[2] <= 7 && pos[3] >= 0) {
						if (!makemove(player, pos, tempBoard)) { returnTempBoard(tempBoard, board); return 1; }
						pos[2]++; pos[3]--;
					}
					pos[2] = j; pos[3] = i;
					while (pos[2] <= 7 && pos[3] <= 7) {
						if (!makemove(player, pos, tempBoard)) { returnTempBoard(tempBoard, board); return 1; }
						pos[2]++; pos[3]++;
					}
					pos[2] = j; pos[3] = i;
					while (pos[2] >= 0 && pos[3] >= 0) {
						if (!makemove(player, pos, tempBoard)) { returnTempBoard(tempBoard, board); return 1; }
						pos[2]--; pos[3]--;
					}
					pos[2] = j; pos[3] = i;
					while (pos[2] >= 0 && pos[3] <= 7) {
						if (!makemove(player, pos, tempBoard)) { returnTempBoard(tempBoard, board); return 1; }
						pos[2]--; pos[3]++;
					}
				} else if (piece == bRook) {
					pos[2] = j; pos[3] = i;
					while (pos[3] <= 7) {
						if (!makemove(player, pos, tempBoard)) { returnCastleStatus(status); returnTempBoard(tempBoard, board); return 1; }
						pos[3]++;
					}
					pos[2] = j; pos[3] = i;
					while (pos[3] >= 0) {
						if (!makemove(player, pos, tempBoard)) { returnCastleStatus(status); returnTempBoard(tempBoard, board); return 1; }
						pos[3]--;
					}
					pos[2] = j; pos[3] = i;
					while (pos[2] <= 7) {
						if (!makemove(player, pos, tempBoard)) { returnCastleStatus(status); returnTempBoard(tempBoard, board); return 1; }
						pos[2]++;
					}
					pos[2] = j; pos[3] = i;
					while (pos[2] >= 0) {
						if (!makemove(player, pos, tempBoard)) { returnCastleStatus(status); returnTempBoard(tempBoard, board); return 1; }
						pos[2]--;
					}
				} else if (piece == bQueen) {
					pos[2] = j; pos[3] = i;
					while (pos[2] <= 7 && pos[3] >= 0) {
						if (!makemove(player, pos, tempBoard)) { returnTempBoard(tempBoard, board); return 1; }
						pos[2]++; pos[3]--;
					}
					pos[2] = j; pos[3] = i;
					while (pos[2] <= 7 && pos[3] <= 7) {
						if (!makemove(player, pos, tempBoard)) { returnTempBoard(tempBoard, board); return 1; }
						pos[2]++; pos[3]++;
					}
					pos[2] = j; pos[3] = i;
					while (pos[2] >= 0 && pos[3] >= 0) {
						if (!makemove(player, pos, tempBoard)) { returnTempBoard(tempBoard, board); return 1; }
						pos[2]--; pos[3]--;
					}
					pos[2] = j; pos[3] = i;
					while (pos[2] >= 0 && pos[3] <= 7) {
						if (!makemove(player, pos, tempBoard)) { returnTempBoard(tempBoard, board); return 1; }
						pos[2]--; pos[3]++;
					}
					pos[2] = j; pos[3] = i;
					while (pos[3] <= 7) {
						if (!makemove(player, pos, tempBoard)) { returnTempBoard(tempBoard, board); return 1; }
						pos[3]++;
					}
					pos[2] = j; pos[3] = i;
					while (pos[3] >= 0) {
						if (!makemove(player, pos, tempBoard)) { returnTempBoard(tempBoard, board); return 1; }
						pos[3]--;
					}
					pos[2] = j; pos[3] = i;
					while (pos[2] <= 7) {
						if (!makemove(player, pos, tempBoard)) { returnTempBoard(tempBoard, board); return 1; }
						pos[2]++;
					}
					pos[2] = j; pos[3] = i;
					while (pos[2] >= 0) {
						if (!makemove(player, pos, tempBoard)) { returnTempBoard(tempBoard, board); return 1; }
						pos[2]--;
					}
				} else if (piece == bKing) {
					pos[2] = j + 1; pos[3] = i + 1; if (!makemove(player, pos, tempBoard)) { returnCastleStatus(status); returnTempBoard(tempBoard, board); return 1; }
					pos[2] = j + 1; pos[3] = i;		if (!makemove(player, pos, tempBoard)) { returnCastleStatus(status); returnTempBoard(tempBoard, board); return 1; }
					pos[2] = j + 1; pos[3] = i - 1; if (!makemove(player, pos, tempBoard)) { returnCastleStatus(status); returnTempBoard(tempBoard, board); return 1; }
					pos[2] = j;		pos[3] = i + 1; if (!makemove(player, pos, tempBoard)) { returnCastleStatus(status); returnTempBoard(tempBoard, board); return 1; }
					pos[2] = j;		pos[3] = i - 1; if (!makemove(player, pos, tempBoard)) { returnCastleStatus(status); returnTempBoard(tempBoard, board); return 1; }
					pos[2] = j - 1; pos[3] = i + 1; if (!makemove(player, pos, tempBoard)) { returnCastleStatus(status); returnTempBoard(tempBoard, board); return 1; }
					pos[2] = j - 1; pos[3] = i;		if (!makemove(player, pos, tempBoard)) { returnCastleStatus(status); returnTempBoard(tempBoard, board); return 1; }
					pos[2] = j - 1; pos[3] = i - 1; if (!makemove(player, pos, tempBoard)) { returnCastleStatus(status); returnTempBoard(tempBoard, board); return 1; }
				}
			}
		}
		return 0;
	}
	/* if all pieces dont have any legal movements (checkmate or stalemate) */
	return 0;
}

void returnTempBoard(int tempBoard[][8], int board[][8]) {
	int i, j;
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            tempBoard[i][j] = board[i][j];
        }
    }
}

void returnCastleStatus(int status[]) {
	if (status[0] != castleW[0])
		castleW[0] = status[0];
	if (status[1] != castleW[1])
		castleW[1] = status[1];
	if (status[2] != castleB[0])
		castleB[0] = status[2];
	if (status[3] != castleB[1])
		castleB[1] = status[3];
}