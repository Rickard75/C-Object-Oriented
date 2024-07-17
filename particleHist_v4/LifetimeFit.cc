#include "LifetimeFit.h"
#include "Event.h"
#include "ParticleReco.h"

#include <cmath>

double mass( const Event& ev );

// constructor
LifetimeFit::LifetimeFit( double min, double max ):
 // initializations
 min_mass(min),
 max_mass(max),
 nAcc(0), 
 sum_mass(0.0), 
 sum_sqr(0.0), 
 mean(0.0), 
 rms(0.0) {
}

// destructor
LifetimeFit::~LifetimeFit() {
}

// add data from a new event
bool LifetimeFit::add( const Event& ev ) {
  // since mass.cc is now encapsulated in ParticleReco, we can call the get_mass() method
  static ParticleReco* pr = ParticleReco::instance();
  double my_mass = pr->get_mass();
  // check for mass being in range
  if (min_mass <= my_mass && my_mass <= max_mass){
    my_mass -= get_min();
    
    // update number of events and sums
    sum_mass += my_mass;
    sum_sqr += my_mass*my_mass;
    nAcc++;
    return true;
  }
  return false;

}

// compute mean and rms
void LifetimeFit::compute() {
  double my_mean = (this->sum_mass*1.0)/(this->nAcc);
  this->mean = my_mean;
  this->rms = sqrt((this->sum_sqr*1.0)/(this->nAcc)-pow(my_mean, 2.0));

  // rescaling
  this->mean += this->min_mass;
}

// return number of selected events
unsigned int LifetimeFit::get_nAcc() const{
  return nAcc;
}

// return mean, rms and min
double LifetimeFit::get_mean() const{
  return mean;
}
double LifetimeFit::get_rms() const{
  return rms;
}
double LifetimeFit::get_min() const {
  return min_mass;
}

/*
The following function is inside Singleton.h:

template <class T>
T* Singleton<T>::instance() {
  // the object is created only once, the first time "instance()" is called
  if ( verbose ) std::cout << "Singleton::instance " << std::endl; 
  
  static T* obj = new T; // every next call will return the same object
  return obj; // return the object pointer
  
}
*/

