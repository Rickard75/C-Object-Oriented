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
    cout << ev->get_eventNumber() << endl
         << ev->get_x() << " " << ev->get_y() << " " << ev->get_z() << endl
         << ev->get_nParticles() << endl;

    for(unsigned int i=0;i<ev->get_nParticles();i++){ //almost everytime runs two times
        cout << ev->get_particle(i)->chg << " " 
             << ev->get_particle(i)->px << " " 
             << ev->get_particle(i)->py << " " 
             << ev->get_particle(i)->pz << endl;
    }
        
    return;
}