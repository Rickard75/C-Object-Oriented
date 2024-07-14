#include <iostream>
#include <fstream>

#include "Event.h"

void clear (const Event* ev){
    
    int dim = ev->nP;
    for(int i=0;i<dim;i++){
        delete ev->p_PList[i]; //deleting Particle one by one
    }
    delete[] ev->p_PList; //deleting PoP

    delete ev; //deleting Event

    return;
}