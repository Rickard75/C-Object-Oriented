#include "Event.h"
// IMPLEMENTATION

// constructor
Event::Event( int n, double x, double y, double z ):
 // initializations
 evNum(n), x(x), y(y), z(z), nP(0) {
  // allocate a buffer for particle pointers
  particles = new part_ptr[10]; //array of 10 ptr
}


// destructor, previous in clear()
Event::~Event() {
  // delete all the particle pointers
  for(unsigned int i=0; i<nP; i++) {
    delete particles[i];
  }
  // delete the pointers array
  delete[] particles;
}

// function that adds one Particle and store it in memory
void Event::add( int charge, double px, double py, double pz ) {

  // check for the number of particles, if maximum reached do nothing
  // and return
  if(nP == 10) return;
  // create the new particle and fill with data
  part_ptr my_party = new Particle{charge,px,py,pz};
  
  // store the new particle pointer in the array and increase counter
  particles[nP] = my_party;
  nP++;

  return;
}

// get event id.
int Event::get_eventNumber() const {
  return evNum;
}


// get decay point coordinates
double Event::get_x() const {
  return x;
}
double Event::get_y() const {
  return y;
}
double Event::get_z() const {
  return z;
}


// get number of particles
unsigned int Event::get_nParticles() const {
  return nP;
}

// get particle
const Event::Particle* Event::get_particle( unsigned int i ) const {
  if (i < 10) return particles[i];
  return nullptr;
}

