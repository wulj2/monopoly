#include "board.h"

board_t::board_t(){
}

board_t::~board_t(){
    if(horiz_empt){
        free(horiz_empt);
        horiz_empt = NULL;
    }
    if(horiz_mask){
        free(horiz_mask);
        horiz_mask = NULL;
    }
}

void board_t::init(int mwl, int nr, int nc){
    horiz_mask = (char*)malloc((mwl+1)*sizeof(char));
    horiz_empt = (char*)malloc((mwl+1)*sizeof(char));
    for(int i = 0; i < mwl; ++i){
        horiz_mask[i] = '-';
        horiz_empt[i] = ' ';
    }
    nrow = nr;
    ncol = nc;
    ttc = 2*(nr+nc) - 4;
}

void board_t::draw(uint8_t* a){
    fprintf(stderr, "\n[%d*%d] board\n\n", nrow, ncol);
    int vi = 0, vl = ttc-1;
    // draw first row
    fprintf(stderr, "%s", UP_LEFT_CORNER);
    for(int i = 0; i < ncol-1; ++i){
        fprintf(stderr, "%s%s", horiz_mask, UP_MIDDLE_MARK);
    }
    fprintf(stderr, "%s%s\n", horiz_mask, UP_RIGHT_CORNER);
    // draw vertical bar
    for(int i = 0; i < ncol; ++i){
        fprintf(stderr, "%s%-*s", VERTICAL_MARK, max_word_len, ARRAY4DRAW[a[vi++]]); // replace horiz_empt to your array content
    }
    fprintf(stderr, "%s\n", VERTICAL_MARK);
    // draw horizon seps
    fprintf(stderr, "%s", LEFT_MIDDLE_MARK);
    fprintf(stderr, "%s%s", horiz_mask, MIDDLE_MARK);
    for(int i = 1; i < ncol-2; ++i){
        fprintf(stderr, "%s%s", horiz_mask, LOW_MIDDLE_MARK);
    }
    fprintf(stderr, "%s%s%s%s\n", horiz_mask, MIDDLE_MARK, horiz_mask, RIGHT_MIDDLE_MARK);
    // draw midele rows
    for(int i = 1; i < nrow-2; ++i){
        fprintf(stderr, "%s%-*s%s", VERTICAL_MARK, max_word_len, ARRAY4DRAW[a[vl--]], VERTICAL_MARK);
        for(int j = 0; j < ncol-3; ++j) fprintf(stderr, "%s%s", horiz_empt, EMPT4MARK);
        fprintf(stderr, "%s%s%-*s%s\n",horiz_empt, VERTICAL_MARK, max_word_len, ARRAY4DRAW[a[vi++]], VERTICAL_MARK);
        fprintf(stderr, "%s%s%s", LEFT_MIDDLE_MARK, horiz_mask, RIGHT_MIDDLE_MARK);
        for(int j = 0; j < ncol-3; ++j) fprintf(stderr, "%s%s", horiz_empt, EMPT4MARK);
        fprintf(stderr, "%s%s%s%s\n", horiz_empt, LEFT_MIDDLE_MARK, horiz_mask, RIGHT_MIDDLE_MARK);
    }
    // draw last rows
    fprintf(stderr, "%s%-*s%s", VERTICAL_MARK, max_word_len, ARRAY4DRAW[a[vi++]], VERTICAL_MARK);
    for(int j = 0; j < ncol-3; ++j) fprintf(stderr, "%s%s", horiz_empt, EMPT4MARK);
    fprintf(stderr, "%s%s%-*s%s\n", horiz_empt, VERTICAL_MARK, max_word_len, ARRAY4DRAW[a[vl--]], VERTICAL_MARK);
    fprintf(stderr, "%s%s%s", LEFT_MIDDLE_MARK, horiz_mask, MIDDLE_MARK);
    for(int j = 0; j < ncol-3; ++j) fprintf(stderr, "%s%s", horiz_mask, UP_MIDDLE_MARK);
    fprintf(stderr, "%s%s%s%s\n", horiz_mask, MIDDLE_MARK, horiz_mask, RIGHT_MIDDLE_MARK);
    for(int i = 0; i < ncol; ++i){
        fprintf(stderr, "%s%-*s", VERTICAL_MARK, max_word_len, ARRAY4DRAW[a[vl--]]);
    }
    fprintf(stderr, "%s\n", VERTICAL_MARK);
    fprintf(stderr, "%s", LOW_LEFT_CORNER);
    for(int i = 1; i < ncol; ++i){
        fprintf(stderr, "%s%s", horiz_mask, LOW_MIDDLE_MARK);
    }
    fprintf(stderr, "%s%s\n\n", horiz_mask, LOW_RIGHT_CORNER);
}

