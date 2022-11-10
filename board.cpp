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
    max_word_len = mwl;
    ind_word_len = mwl+1;
    if(ind_word_len < 0) ind_word_len = 1;
    horiz_mask = (char*)malloc((mwl+3)*sizeof(char));
    horiz_empt = (char*)malloc((mwl+3)*sizeof(char));
    for(int i = 0; i < mwl+2; ++i){
        horiz_mask[i] = '-';
        horiz_empt[i] = ' ';
    }
    horiz_mask[mwl+2] = horiz_empt[mwl+2] = '\0';
    nrow = nr;
    ncol = nc;
    ttc = 2*(nr+nc) - 4;
}

void board_t::draw(cell_t** pcells){
    fprintf(stderr, "%s%sboard occupy(o) and price(p) status\n", horiz_empt, EMPT4MARK);
    int vi = 0, vl = ttc-1, ci = 0, di = ttc-1;
    // draw index
    fprintf(stderr, "%s%s", horiz_empt, EMPT4MARK); 
    for(int i = 0; i < ncol; ++i){
        fprintf(stderr, "%s%-*d%s",  EMPT4MARK, ind_word_len, ci++,  EMPT4MARK);
    }
    fprintf(stderr, "\n");
    // draw first row
    fprintf(stderr, "%s%s", horiz_empt, UP_LEFT_CORNER);
    for(int i = 0; i < ncol-1; ++i){
        fprintf(stderr, "%s%s", horiz_mask, UP_MIDDLE_MARK);
    }
    fprintf(stderr, "%s%s\n", horiz_mask, UP_RIGHT_CORNER);
    fprintf(stderr, "%*s", max_word_len+2, "GO->");
    // draw vertical bar
    for(int i = 0; i < ncol; ++i){
        fprintf(stderr, "%so:%-*s", VERTICAL_MARK, max_word_len, ARRAY4DRAW[pcells[vi++]->umask]);
    }
    vi -= ncol;
    fprintf(stderr, "%s\n", VERTICAL_MARK);
    fprintf(stderr, "%s", horiz_empt);
    for(int i = 0; i < ncol; ++i){
        fprintf(stderr, "%sp:%-*d", VERTICAL_MARK, max_word_len, pcells[vi++]->price);
    }
    fprintf(stderr, "%s\n", VERTICAL_MARK);
    // draw horizon seps
    fprintf(stderr, "%s%s", horiz_empt, LEFT_MIDDLE_MARK);
    fprintf(stderr, "%s%s", horiz_mask, MIDDLE_MARK);
    for(int i = 1; i < ncol-2; ++i){
        fprintf(stderr, "%s%s", horiz_mask, LOW_MIDDLE_MARK);
    }
    fprintf(stderr, "%s%s%s%s\n", horiz_mask, MIDDLE_MARK, horiz_mask, RIGHT_MIDDLE_MARK);
    // draw midele rows
    for(int i = 1; i < nrow-2; ++i){
        fprintf(stderr, "%s%*d", EMPT4MARK, ind_word_len, di--);
        fprintf(stderr, "%so:%-*s%s", VERTICAL_MARK, max_word_len, ARRAY4DRAW[pcells[vl]->umask], VERTICAL_MARK);
        for(int j = 0; j < ncol-3; ++j) fprintf(stderr, "%s%s", horiz_empt, EMPT4MARK);
        fprintf(stderr, "%s%so:%-*s%s", horiz_empt, VERTICAL_MARK, max_word_len, ARRAY4DRAW[pcells[vi]->umask], VERTICAL_MARK);
        fprintf(stderr, "%d\n", ci++);
        fprintf(stderr, "%s", horiz_empt);
        fprintf(stderr, "%sp:%-*d%s", VERTICAL_MARK, max_word_len, pcells[vl]->price, VERTICAL_MARK);
        for(int j = 0; j < ncol-3; ++j) fprintf(stderr, "%s%s", horiz_empt, EMPT4MARK);
        fprintf(stderr, "%s%sp:%-*d%s\n", horiz_empt, VERTICAL_MARK, max_word_len, pcells[vi]->price, VERTICAL_MARK);
        --vl; ++vi;
        fprintf(stderr, "%s", horiz_empt);
        fprintf(stderr, "%s%s%s", LEFT_MIDDLE_MARK, horiz_mask, RIGHT_MIDDLE_MARK);
        for(int j = 0; j < ncol-3; ++j) fprintf(stderr, "%s%s", horiz_empt, EMPT4MARK);
        fprintf(stderr, "%s%s%s%s\n", horiz_empt, LEFT_MIDDLE_MARK, horiz_mask, RIGHT_MIDDLE_MARK);
    }
    // draw last rows
    fprintf(stderr, "%s%*d", EMPT4MARK, ind_word_len, di--);
    fprintf(stderr, "%so:%-*s%s", VERTICAL_MARK, max_word_len, ARRAY4DRAW[pcells[vi]->umask], VERTICAL_MARK);
    for(int j = 0; j < ncol-3; ++j) fprintf(stderr, "%s%s", horiz_empt, EMPT4MARK);
    fprintf(stderr, "%s%so:%-*s%s", horiz_empt, VERTICAL_MARK,max_word_len, ARRAY4DRAW[pcells[vi]->umask], VERTICAL_MARK);
    fprintf(stderr, "%d\n", ci++);
    fprintf(stderr, "%s", horiz_empt);
    fprintf(stderr, "%sp:%-*d%s", VERTICAL_MARK, max_word_len, pcells[vi]->price, VERTICAL_MARK);
    for(int j = 0; j < ncol-3; ++j) fprintf(stderr, "%s%s", horiz_empt, EMPT4MARK);
    fprintf(stderr, "%s%sp:%-*d%s\n", horiz_empt, VERTICAL_MARK,max_word_len, pcells[vi]->price, VERTICAL_MARK);
    --vl; ++vi;
    fprintf(stderr, "%s", horiz_empt);
    fprintf(stderr, "%s%s%s", LEFT_MIDDLE_MARK, horiz_mask, MIDDLE_MARK);
    for(int j = 0; j < ncol-3; ++j) fprintf(stderr, "%s%s", horiz_mask, UP_MIDDLE_MARK);
    fprintf(stderr, "%s%s%s%s\n", horiz_mask, MIDDLE_MARK, horiz_mask, RIGHT_MIDDLE_MARK);
    fprintf(stderr, "%s%*d", EMPT4MARK, ind_word_len, di--);
    for(int j = 0; j < ncol; ++j){
        fprintf(stderr, "%so:%-*s", VERTICAL_MARK, max_word_len, ARRAY4DRAW[pcells[vl--]->umask]);
    }
    vl += ncol;
    fprintf(stderr, "%s<-JAIL\n", VERTICAL_MARK);
    fprintf(stderr, "%s", horiz_empt);
    for(int j = 0; j < ncol; ++j){
        fprintf(stderr, "%sp:%-*d", VERTICAL_MARK, max_word_len, pcells[vl--]->price);
    }
    fprintf(stderr, "%s\n", VERTICAL_MARK);
    fprintf(stderr, "%s%s", horiz_empt, LOW_LEFT_CORNER);
    for(int i = 1; i < ncol; ++i){
        fprintf(stderr, "%s%s", horiz_mask, LOW_MIDDLE_MARK);
    }
    fprintf(stderr, "%s%s\n", horiz_mask, LOW_RIGHT_CORNER);
    // foot index
    fprintf(stderr, "%s%s%s%s", horiz_empt, EMPT4MARK, horiz_empt, EMPT4MARK); 
    for(int i = 0; i < ncol-1; ++i){
        fprintf(stderr, "%s%-*d%s",  EMPT4MARK, ind_word_len, di--,  EMPT4MARK);
    }
    fprintf(stderr, "\n");
}

