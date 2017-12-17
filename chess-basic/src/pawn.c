extern int checkPosition(int row, int col, int b[][8]);

extern void completemove(int pos[], int b[][8]);

extern void setPassant(int column, int player);

extern int checkPassant(int row, int column, int player);

extern int kingUnderAttack(int player, int board[][8]);

int pawn(int pos[], int player, int board[][8]) {
    /*[col][row][col][row]*/
    /*pos[] contains current positions and new positions [0][1]=current [2][3] = new*/
    int tempBoard[8][8];
    int i, j;
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            tempBoard[i][j] = board[i][j];
        }
    }

    if (player) {
        /*player is black*/
        if (pos[3] == pos[1] + 1 && pos[2] == pos[0] + 1) {
            /*move south east*/
            if (checkPosition(pos[3], pos[2], board)) {
                /*piece at position, therefore move is legal*/
                /*add method to check if reached end of board to swap piece*/
                completemove(pos, tempBoard);
                if (kingUnderAttack(player, tempBoard)) {
                    return 0;
                }
                return 1;
                /*a pawn was at new pos the previous round, therefore move is legal*/
            } else if (checkPassant(pos[1], pos[2], player)) {
                /*remove the pawn that moved last round*/
                /* TODO (kingUnderAttack): check en-passant move is legal later */
                board[pos[3] - 1][pos[2]] = 0;
                return 1;
            }
        } else if (pos[3] == pos[1] + 1 && pos[2] == pos[0] - 1) {
            /*move south west*/
            if (checkPosition(pos[3], pos[2], board)) {
                /*piece at position, therefore move is legal*/
                /*add method to check if reached end of board to swap piece*/
                completemove(pos, tempBoard);
                if (kingUnderAttack(player, tempBoard)) {
                    return 0;
                }
                return 1;
                /*a pawn was at new pos the previous round, therefore move is legal*/
            } else if (checkPassant(pos[1], pos[2], player)) {
                /*remove the pawn that moved last round*/
                board[pos[3] - 1][pos[2]] = 0;
                return 1;
            } else {
                /*illegal move*/
                return 0;
            }
        } else if (pos[3] == pos[1] + 1 && pos[2] == pos[0]) {
            /*Move one step south*/
            if (!checkPosition(pos[3], pos[2], board)) {
                /*piece not at position therefore move is legal*/
                /*add method to check if reached end of board to swap piece*/
                completemove(pos, tempBoard);
                if (kingUnderAttack(player, tempBoard)) {
                    return 0;
                }
                return 1;
            } else {
                /*legal move*/
                return 0;
            }
        } else if (pos[3] == pos[1] + 2 && pos[2] == pos[0]) {
            /*Move two steps south*/
            if (!checkPosition(pos[3], pos[2], board) && !checkPosition(pos[3] - 1, pos[2], board) &&
                (pos[1] == 1 || pos[1] == 6)) {
                completemove(pos, tempBoard);
                if (kingUnderAttack(player, tempBoard)) {
                    return 0;
                }
                /*No piece at new position, middle position, and not moved, therefore move is legal*/
                completemove(pos, board);
                /*set the previous collumn position to the
                * passant array. This is done after the move is made
                * because completemove resets the passant arrays.*/
                setPassant(pos[0], player);
                return 2;
            } else {
                /*illegal move*/
                return 0;
            }
        } else {
            /*illegal move*/
            return 0;
        }
    } else {
        /*player is white*/
        if (pos[3] == pos[1] - 1 && pos[2] == pos[0] + 1) {
            /*move north east*/
            if (checkPosition(pos[3], pos[2], board)) {
                /*piece at position, therefore move is legal*/
                /*add method to check if reached end of board to swap piece*/
                completemove(pos, tempBoard);
                if (kingUnderAttack(player, tempBoard)) {
                    return 0;
                }
                return 1;

                /*a pawn was at new pos the previous round, therefore move is legal*/
            } else if (checkPassant(pos[1], pos[2], player)) {
                /*remove the pawn that moved last round*/
                board[pos[3] + 1][pos[2]] = 0;
                return 1;
            }
        } else if (pos[3] == pos[1] - 1 && pos[2] == pos[0] - 1) {
            /*move north west*/
            if (checkPosition(pos[3], pos[2], board)) {
                /*piece at position, therefore move is legal*/
                /*add method to check if reached end of board to swap piece*/
                completemove(pos, tempBoard);
                if (kingUnderAttack(player, tempBoard)) {
                    return 0;
                }
                return 1;
                /*a pawn was at new pos the previous round, therefore move is legal*/
            } else if (checkPassant(pos[1], pos[2], player)) {
                /*remove the pawn that moved last round*/
                board[pos[3] + 1][pos[2]] = 0;
                return 1;
            } else {
                /*illegal move*/
                return 0;
            }
        } else if (pos[3] == pos[1] - 1 && pos[2] == pos[0]) {
            /*Move one step north*/
            if (!checkPosition(pos[3], pos[2], board)) {
                /*piece not at position therefore move is legal*/
                /*add method to check if reached end of board to swap piece*/
                completemove(pos, tempBoard);
                if (kingUnderAttack(player, tempBoard)) {
                    return 0;
                }
                return 1;
            } else {
                /*illegal move*/
                return 0;
            }
        } else if (pos[3] == pos[1] - 2 && pos[2] == pos[0]) {
            /*Move two steps north*/
            if (!checkPosition(pos[3], pos[2], board) && !checkPosition(pos[3] + 1, pos[2], board) &&
                (pos[1] == 1 || pos[1] == 6)) {
                completemove(pos, tempBoard);
                if (kingUnderAttack(player, tempBoard)) {
                    return 0;
                }
                /*No piece at new position, middle position, and not moved, therefore move is legal*/
                completemove(pos, board);
                /*set the previous collumn position to the
                * passant array. This is done after the move is made
                * because completemove resets the passant arrays.*/
                setPassant(pos[0], player);
                return 2;
            } else {
                /*illegal move*/
                return 0;
            }
        } else {
            /*illegal move*/
            return 0;
        }
    }
    /*illegal move*/
    return 0;
}
