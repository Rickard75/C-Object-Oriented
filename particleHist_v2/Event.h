#ifndef Event_h
#define Event_h
#include <vector>

// INTERFACE
class Event {

 public:

  // CONSTRUCTOR
  Event( int n, double x, double y, double z ); // create an event with number "n"
                                             // and coordinates x, y, z
  // DESTRUCTOR
  ~Event();

  // composite object Particle to hold all information for each particle
  // ( electric charge and x,y,z momentum components )
  struct Particle {
    int chg;
    double px, py, pz;
  };
  typedef const Particle* part_ptr;

  // OTHER FUNCTIONS
  // add a particle to the event
  void add( int charge, double px, double py, double pz );
  // get event id.
  int get_eventNumber() const;
  // get decay point coordinates
  double get_x() const;
  double get_y() const;
  double get_z() const;
  // get number of particles
  unsigned int get_nParticles() const;
  // get particle
  part_ptr get_particle( unsigned int i ) const;

 private:
  // here data previous in the struct
  // event-specific informations:
  int evNum; // event id
  double x,y,z; // decay point

  // particles: vector of pointers to Particles
  // particle.size() is the new nP
  std::vector<Particle*> particles; 

};

#endif

