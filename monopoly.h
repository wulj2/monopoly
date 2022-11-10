#ifndef MONOPOLY_H
#define MONOPOLY_H


#include "cell.h"
#include "dice.h"
#include "board.h"
#include <ctype.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define IDX4USER 0
#define IDX4PC 1

/* player */
struct player_t{
    uint8_t uid = 0; // 0x0:none, 0x1:user, 0x2:PC
    char* uname = NULL; // user name
    int32_t asset = 0; // asset accumulated
    int32_t pos = 0; // position
    int32_t rstep = 0; // random step

    player_t(){};
    
    ~player_t(){
        if(uname){
            free(uname);
            uname = NULL;
        }
    }

    bool bankrupt(){
        return asset < 0;
    }
};


/* monopoly options */
struct opt_t{
    // board opts
    int32_t tot_cell = 38; // total cells
    int32_t nrow = 10, ncol = 11; // board dims
    int32_t idx4go = 0; // index for go cell
    int32_t idx4jail = 19; // index for jail cell
    int32_t minstep = 1; // min steps
    int32_t maxstep = 6; // max steps
    int32_t cp_min = 10; // cell min init price
    int32_t cp_max = 300; // cell max init price
    // price and fine opts
    int32_t prize4go = 200; // prize for go cell hit
    double fine4hitop1 = 0.1; // fine for hit other player cell
    double fine4hitop2 = 0.2; // fine for hit other player consecutive cells
    double fine4hitopm = 0.2; // max fine for hit other player cell
    double fine4buyoff = 0.05; // fine for buy already bought cell
    double price4invest = 0.5; // price for bought off cell
    // board
    cell_t** pcells = NULL; // board cell internal
    board_t* pboard = NULL; // board for drawing
    int maxcw = 4; // max cell width
    // pps
    int32_t init_asset = 5000; // init assets
    player_t** pps = NULL; // players
    // others
    bool initialized = false;
    char ans = '\0';

    opt_t(){};
    ~opt_t();

    void init();
    void show();
    void getans(const char* pre);
    void move(player_t* p);
    void run1round();
};

#endif
