#ifndef CELL_H
#define CELL_H


#include <ctype.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define OWN_BY_NON_MASK 0
#define OWN_BY_USER_MASK 1
#define OWN_BY_PC_MASK 2


/* cell of player board */
struct cell_t{
    uint8_t umask = 0; // ownership mask id(0x0:none, 0x1:user, 0x2:PC)
    uint8_t imask = 0; // invest mask id(0x0:none, 0x1:user, 0x2:PC)
    int32_t price = 0; // cell price, random set in [10, 300] initially
};

#endif
