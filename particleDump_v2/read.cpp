#include <iostream>
#include <fstream>
using namespace std;

#include "Event.h"

/*
description: read() takes as argument an input file stream,
             reads an event and returns a pointer to the event or a null pointer 
             at the file end; the creation of the event is done dynamically in order to save
             memory space because of the useless storage unless archived
*/

Event* read( ifstream& file ) { //'file' is a new nickname for 'in_file'

    //pointer, identifier, #particles
    Event* ev;
    int id;     //aka evNum
    int n;      //aka nP
    
    //dynamical Event creation if successfull reading
    if (file >> id){
        ev = new Event; //creation of a pointer
    } else {
        return nullptr; //file has ended!
    }

    //setting id, reading position, setting #particles 
    ev->evNum = id; 
    file >> ev->x >> ev->y >> ev->z >> ev->nP;
    n = ev->nP;

    //creation of dynamical PoP, a pointer (=array) of pointers to Particle structs
    ev->p_PList = new Particle*[n]; // each Event has one or more Particle detected

    //read data from all Particle and fill the PoP with data
    for(int i=0;i<n;i++){
        ev->p_PList[i] = new Particle; //creation of new Particle struct at the i-th position of the PoP
        file >> ev->p_PList[i]->chg;
        file >> ev->p_PList[i]->px;
        file >> ev->p_PList[i]->py;
        file >> ev->p_PList[i]->pz;
    }

    return ev; //return the pointer of the current event
}