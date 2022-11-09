#ifndef DICE_H
#define DICE_H


#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <stdint.h>

/* dice structure */
struct dice_t{
    int min_ = 1; // min inclusive
    int max_ = 6; // max inclusive

    void init(int min, int max);
    int roll();
};

#endif
