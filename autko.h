#ifndef INTERGALAKTYCZNYUBER_AUTKO_H
#define INTERGALAKTYCZNYUBER_AUTKO_H
#include "autko.h"

enum state { IDLE,DRIVINGTOCLIENT,DRIVINGWITHCLIENT };
struct Autko {
    Edge loc;
    Dir dir;
    Cell cel;
    state state=IDLE;
};


#endif //INTERGALAKTYCZNYUBER_AUTKO_H