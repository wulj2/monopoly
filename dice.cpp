#include "dice.h"

void dice_t::init(int min, int max){
    min_ = min;
    max_ = max+1;

}

int dice_t::roll(){
    int ret = min_-1;
    while(ret < min_){
        srand(time(NULL));
        ret = random()%(max_);
    }
    return ret;
}
