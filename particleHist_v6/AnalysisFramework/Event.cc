#include "Event.h"
#include <vector>
// IMPLEMENTATION

// constructor
Event::Event( int n, double x, double y, double z ):
 // initializations
 evNum(n), x(x), y(y), z(z) {
  // allocate a buffer for particle pointers
  particles.reserve(10); //vector
}


// destructor, previous in clear()
Event::~Event() {
  // delete the vector of particles pointers
  // for (unsigned int i=0; i < particles.size(); i++){
  //  delete particles[i];
  //}
  particles.clear(); // same result as above
}

// function that adds one Particle and store it in memory
void Event::add( int charge, double px, double py, double pz ) {

  // check for the number of particles, if maximum reached do nothing
  if(particles.size() == particles.capacity()) return;

  // create the new particle and fill with data
  Particle* my_party = new Particle{charge,px,py,pz};
  particles.push_back(my_party);

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
  return particles.size();
}

// get particle
const Event::Particle* Event::get_particle( unsigned int i ) const {
  if (i < particles.size()) return particles[i];
  return nullptr;
}

