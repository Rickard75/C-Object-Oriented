#include <iostream>
#include <fstream>
using namespace std;

#include "Event.h"

/*
description: this short code creates a function "dump" linked to the event
                pointetr and prints out values on the screen.
*/

void dump(const Event* ev){

    //write data of the event
    cout << ev->evNum << endl
         << ev->x << " " << ev->y << " " << ev->z << endl
         << ev->nP << endl;

    for(int i=0;i<ev->nP;i++){ //almost everytime runs two times
        cout << ev->p_PList[i]->chg << " " 
             << ev->p_PList[i]->px << " " 
             << ev->p_PList[i]->py << " " 
             << ev->p_PList[i]->pz << endl;
    }
        
    return;
}