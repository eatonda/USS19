#include "aiBoards.h"

int **get_ai_board(int size, int num){

    int **board = (int**) malloc(sizeof(int *) * size);
    for (int i = 0; i < size; i++){
        board[i] = (int *) malloc(sizeof(int) * size);
        for (int j = 0; j < size; j++){
            board[i][j] = -1;
        }
    }

    int shipSizes [] = {5, 4, 3, 2, 2, 3, 4, 2, 2, 2};

    int numHits = 0;

    for (int i = 0; i < num; i++) numHits += shipSizes[i];

    int cnt = 0;
    while(1){
        int r = rand() % size;
        int c = rand() % size;
        if ( board[r][c] == -1){
            board[r][c] = 0;
            cnt++;
        }

        if (cnt >= numHits) break;
    }


    return board;
}
