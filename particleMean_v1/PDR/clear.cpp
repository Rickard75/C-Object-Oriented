#include <iostream>
#include <fstream>

#include "Event.h"

void clear (const Event* ev){
    
    //delete Particles, their pointer and the Event itself
    int dim = ev->nP;
    for(int i=0;i<dim;i++){
        delete ev->p_PList[i];
    }
    delete[] ev->p_PList;

    //delete Event
    delete ev;

    return;
}