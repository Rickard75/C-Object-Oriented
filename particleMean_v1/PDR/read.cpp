#include <iostream>
#include <fstream>
using namespace std;

#include "Event.h"

/*
description: this short code about the read() function takes as argument an input file stream,
                reads an event and returns a pointer to the event or a null pointer 
                at the file end; the creation of the event is done dynamically in order to save
                memory space because of the useless storage unless archived
*/

Event* read( ifstream& file ) { //'file' is a new nickname for 'in_file'

    //pointer, identifier, no. of particles
    Event* ev;
    int id;     //aka evNum
    int n;      //aka nP
    
    //dynamical Event creation if successfull reading
    if (file >> id){
        ev = new Event; //creation of a pointer
    } else {
        return nullptr; //file has ended!
    }

    //set the id member, read position of decay, read no. of particles involved in the event
    ev->evNum = id; 
    file >> ev->x >> ev->y >> ev->z >> ev->nP;
    n = ev->nP;

    //create a dynamical PoP, a pointer (=array) of pointers to Particle structs
    ev->p_PList = new Particle*[n]; //for each particle detected a Particle struct is created
                                    // In this way each event (pointer) has one or more particle
                                    // associated to it (array of Particles), from this the needing
                                    // of using a PoP.

    //read data from all Particle objects and fill the PoP with their addresses
    for(int i=0;i<n;i++){
        ev->p_PList[i] = new Particle; //creation of a new Particle struct at the i-th position of the PoP
        file >> ev->p_PList[i]->chg;
        file >> ev->p_PList[i]->px;
        file >> ev->p_PList[i]->py;
        file >> ev->p_PList[i]->pz;
    }

    return ev; //return the pointer of the current event
}