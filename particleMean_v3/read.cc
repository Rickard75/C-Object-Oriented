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

    // pass the event number and the decay point coordinates to the constructor,
    int id=0;
    double x = 0.0, y = 0.0, z = 0.0;
    unsigned int numP = 0;
    Event* evento;

    if( !(file >> id) ) return nullptr; 
    file >> x >> y >> z;
    evento = new Event(id,x,y,z); // creation of Event object if successfull reading
    file >> numP; // getting private member nP of object evento
    //evento->get_nParticles() = numP; //gives error, can't assign value to call to function
    

    // ---------------------------------------------------------SONO QUI-------------------------------------------------------------------

    //  call the "add" function in the loop reading particles.
    int charge = 0;
    double px = 0.0;
    double py = 0.0;
    double pz = 0.0;
    for(unsigned int i=0;i<numP;i++){
        file >> charge >> px >> py >> pz;
        evento->add(charge, px, py, pz);
    }

    return evento; //return the pointer of the current event
}