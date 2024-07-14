#include "EventReadFromFile.h"

#include "Event.h"

#include <iostream>
#include <fstream>
#include <string>

using namespace std;


// read data from file "name"
EventReadFromFile::EventReadFromFile( const string& name ) {
  file = new ifstream( name.c_str(), ios::binary );
}


EventReadFromFile::~EventReadFromFile() {
  delete file;
}


// get an event
const Event* EventReadFromFile::get() {
  return readFile();
}

// TO MODIFY
// read an event
const Event* EventReadFromFile::readFile() {

  // pass the event number and the decay point coordinates to the constructor,
    int id=0;
    double x = 0.0, y = 0.0, z = 0.0;
    unsigned int numP = 0;
    Event* evento;

    if( !(*file >> id) ) return nullptr; 
    *file >> x >> y >> z;
    evento = new Event(id,x,y,z); // creation of Event object if successfull reading
    *file >> numP; // getting private member nP of object evento
    //evento->get_nParticles() = numP; //gives error, can't assign value to call to function
    

    // ---------------------------------------------------------SONO QUI-------------------------------------------------------------------

    //  call the "add" function in the loop reading particles.
    int charge = 0;
    double px = 0.0;
    double py = 0.0;
    double pz = 0.0;
    for(unsigned int i=0;i<numP;i++){
        *file >> charge >> px >> py >> pz;
        evento->add(charge, px, py, pz);
    }

    return evento; //return the pointer of the current event

}

