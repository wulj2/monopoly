#include "monopoly.h"

opt_t::~opt_t(){
    if(pcells){
        for(int i = 0; i < tot_cell; ++i){
            if(pcells[i]){
                delete pcells[i];
                pcells[i] = NULL;
            }
        }
        free(pcells);
        pcells = NULL;
    }
    if(pps){
        for(int i = 0; i < 2; ++i){
            if(pps[i]){
                delete pps[i];
                pps[i] = NULL;
            }
        }
        free(pps);
        pps = NULL;
    }
    if(pboard){
        delete pboard;
         pboard = NULL;
    }
}

void opt_t::init(){
    if(initialized) return;
    // init board
    tot_cell = 2*(nrow+ncol)-4;
    idx4go = 0;
    idx4jail = nrow+ncol-2;
    dice_t* pdice = new dice_t();
    pdice->init(cp_min, cp_max);
    pcells = (cell_t**)malloc(tot_cell*sizeof(cell_t*));
    for(int i = 0; i < tot_cell; ++i){
        pcells[i] = new cell_t();
        pcells[i]->umask = OWN_BY_NON_MASK;
        pcells[i]->imask = OWN_BY_NON_MASK;
        pcells[i]->price = pdice->roll();
    }
    delete pdice;
    // init pps
    pps = (player_t**)malloc(2*sizeof(player_t*));
    pps[IDX4USER] = new player_t();
    pps[IDX4PC] = new player_t();
    pps[IDX4USER]->asset = pps[IDX4PC]->asset = init_asset;
    pps[IDX4USER]->pos = pps[IDX4PC]->pos = idx4go;
    pps[IDX4USER]->uid = OWN_BY_USER_MASK;
    pps[IDX4PC]->uid = OWN_BY_PC_MASK;
    pps[IDX4USER]->uname = strdup("You");
    pps[IDX4PC]->uname = strdup("PC");
    initialized = true;
    // init board
    pboard = new board_t();
    pboard->init(maxcw, nrow, ncol);
}

void opt_t::show(){
    fprintf(stderr, "%sUser status\n", pboard->horiz_empt);
    fprintf(stderr, "%s┌----------┬----------┬----------┐\n", pboard->horiz_empt);
    fprintf(stderr, "%s|%-10s|%-10s|%-10s|\n", pboard->horiz_empt, "User", "Assets", "Pos");
    for(int i = 0; i < 2; ++i){
        fprintf(stderr, "%s├----------┼----------┼----------┤\n", pboard->horiz_empt);
        fprintf(stderr, "%s|%-10s|%-10d|%-10d|\n", pboard->horiz_empt, pps[i]->uname, pps[i]->asset, pps[i]->pos);
    }
    fprintf(stderr, "%s└----------┴----------┴----------┘\n", pboard->horiz_empt);
    pboard->draw(pcells);
}

void opt_t::getans(const char* pre){
    ans = '\0';
    do{
        fprintf(stderr, "%s or not(n/y):", pre);
        scanf(" %c", &ans);
    }while(toupper(ans) != 'Y' && toupper(ans) != 'N');
    ans = toupper(ans);
}

void opt_t::move(player_t* p){
    p->pos = (p->pos + p->rstep)%tot_cell;
    if(p->pos == idx4go){ // prize for GO hit
        p->asset += prize4go;
        return;
    }
    if(p->pos == idx4jail){ // do nothing
        fprintf(stderr, "\nYou hit JAIL, wait for another around.\n");
        return;
    }
    if(pcells[p->pos]->umask & p->uid){ // already occupied, do nothing
        return;
    }
    if(pcells[p->pos]->umask == OWN_BY_NON_MASK){ // not occupied, just buy/invest
        fprintf(stderr, "cell %d price is %d\n", p->pos, pcells[p->pos]->price);
        getans("Buy");
        if(ans == 'Y'){
            p->asset -= pcells[p->pos]->price;
            getans("Invest");
            if(ans == 'Y'){
                p->asset -= pcells[p->pos]->price*price4invest;
                pcells[p->pos]->price *= (1+price4invest);
                pcells[p->pos]->imask |= p->uid;
            }
            pcells[p->pos]->umask |= p->uid;
        }
        return;
    }
    if(pcells[p->pos]->umask & (3-p->uid)){ // occupied by other people, then fine you
        double fine = fine4hitop1;
        if(p->pos-1 > 0 && pcells[p->pos-1]->umask & (3-p->uid)){
            fine = fine4hitop2;
        }else if(p->pos+1 < tot_cell && pcells[p->pos+1]->umask & (3-p->uid)){
            fine = fine4hitop2;
        }
        if(pcells[p->pos]->imask & pcells[p->pos]->umask) fine += fine4buyoff;
        if(fine > fine4hitopm) fine = fine4hitopm;
        fine *= pcells[p->pos]->price;
        fprintf(stderr, "%s fined by %d\n", p->uname, (int)fine);
        p->asset -= fine;
        return;
    }
}

void opt_t::run1round(){
    // init
    init();
    // dice for steps
    dice_t* pd4step = new dice_t();
    pd4step->init(minstep, maxstep);
    while(1){
        show();
        if(pps[0]->bankrupt() || pps[1]->bankrupt()) break;
        getans("Continue");
        if(ans == 'N') break;
        pps[IDX4USER]->rstep = pd4step->roll();
        fprintf(stderr, "rolling dice for User(p:%d,a:%d) and got:%d\n", 
                        pps[IDX4USER]->pos,
                        pps[IDX4USER]->asset,
                        pps[IDX4USER]->rstep);
        move(pps[IDX4USER]);
        show();
        pps[IDX4PC]->rstep = pd4step->roll();
        fprintf(stderr, "rolling dice for PC(p:%d,a:%d) and got:%d\n",
                        pps[IDX4PC]->pos,
                        pps[IDX4PC]->asset,
                        pps[IDX4PC]->rstep);
        move(pps[IDX4PC]);
    }
}

bool opt_t::valid(){
    if(nrow < BOARD_MIN_DIM || ncol < BOARD_MIN_DIM){
        fprintf(stderr, "row and column must be greater than %d!\n", BOARD_MIN_DIM);
        return false;
    }
    return true;
}

void mp_usage(opt_t* opt, char* arg0){
    fprintf(stderr, "\n");
    fprintf(stderr, "Program: a siple version monopoly game\n\n");
    fprintf(stderr, "Usage: %s [options]\n\n", arg0);
    fprintf(stderr, "Options: -r INT  row number of board [%d]\n", opt->nrow);
    fprintf(stderr, "         -c INT  col number of board [%d]\n", opt->ncol);
    fprintf(stderr, "         -a INT  initial asset for users [%d]\n", opt->init_asset);
    fprintf(stderr, "\n");
}

int mp_main(int argc, char** argv){
    opt_t opt;
    if(argc == 1) {
        mp_usage(&opt, argv[0]);
        return 0;
    }
    int c = -1;
    while((c = getopt(argc, argv, "r:c:a:h")) >= 0) {
        switch(c) {
            case 'r': opt.nrow = atoi(optarg); break;
            case 'c': opt.ncol = atoi(optarg); break;
            case 'a': opt.init_asset = atoi(optarg); break;
            case 'h': mp_usage(&opt, argv[0]); return 0; break;
            default: break;
        }
    }
    if(opt.valid()){
        opt.init();
        opt.run1round();
    }
    return 0;
}

int main(int argc, char** argv){
    return mp_main(argc, argv);
}
