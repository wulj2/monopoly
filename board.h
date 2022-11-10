#ifndef BOARD_H
#define BOARD_H

#include "cell.h"
#include <stdio.h>
#include <stdlib.h>

#define ROW_CNT 10
#define COL_CNT 8

#define UP_LEFT_CORNER "┌"
#define UP_RIGHT_CORNER "┐"
#define LOW_LEFT_CORNER "└"
#define LOW_RIGHT_CORNER "┘"
#define UP_MIDDLE_MARK "┬"
#define LOW_MIDDLE_MARK "┴"
#define LEFT_MIDDLE_MARK "├"
#define RIGHT_MIDDLE_MARK "┤"
#define MIDDLE_MARK "┼"
#define VERTICAL_MARK "|"
#define EMPT4MARK " "

#define SYMBOIDX4GO 4
#define SYMBOIDX4JAIL 5

static const char* ARRAY4DRAW[6] = {
    "0", "1", "2", "3", "GO", "JAIL"
};

struct board_t{
    int nrow = 10;
    int ncol = 8;
    int ttc = 0;
    int max_word_len = 4;
    int ind_word_len = 3;
    char* horiz_mask = NULL;
    char* horiz_empt = NULL;

    board_t();
    ~board_t();

    void init(int mwl, int nr, int nc);
    void draw(cell_t** pcells);
};

#endif
