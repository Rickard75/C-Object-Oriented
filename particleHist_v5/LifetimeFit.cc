#include "LifetimeFit.h"
#include "Event.h"
#include "ParticleReco.h"
#include "ProperTime.h"
#include "QuadraticFitter.h"

#include <cmath>

double mass( const Event& ev );

// constructor
LifetimeFit::LifetimeFit( double min, double max, double min_time, double max_time, double min_scan, double max_scan, double scan_step ):
 // initializations
 min_mass(min),
 max_mass(max),
 min_time(min_time),
 max_time(max_time),
 min_scan(min_scan),
 max_scan(max_scan),
 scan_step(scan_step) {
}

// destructor
LifetimeFit::~LifetimeFit() {
}

// add data from a new event
bool LifetimeFit::add( const Event& ev ) {
  // since mass.cc is now encapsulated in ParticleReco, we can call the get_mass() method
  static ParticleReco* pr = ParticleReco::instance();
  static ProperTime* pt = ProperTime::instance();
  double my_mass = pr->get_mass();
  double my_time = pt->get_time();
  // check for mass being in range
  if (min_mass <= my_mass && my_mass <= max_mass){
    if(min_time <= my_time && my_time <= max_time){
      times.push_back(my_time);
      return true;
    }
  }
  return false;

}

// compute mean and rms
void LifetimeFit::compute() {
  QuadraticFitter* qf = new QuadraticFitter(); // creating a QuadraticFitter object
  for (double t_s = min_scan; t_s <= max_scan; t_s += scan_step){
    double likelihood = 0; // initializing likelihood
    double t_i = 0; // initializing single time value
    for (unsigned int i=0; i<times.size(); i++){
      t_i = times[i];
      likelihood += (t_i/t_s) + log(t_s) + log( exp(-min_time/t_s) - exp(max_time/t_s ) );
      
      qf->add(t_s, likelihood);
    }
  }
  particle_lifetime_mean = - qf->b() / (2*qf->c()); // lifetime mean
  double &min = particle_lifetime_mean;
  double min_likelihood = qf->a() + qf->b()*min + qf->c()*(pow(min,2)); // useless but computed for completeness
  particle_lifetime_rms = sqrt( 1/( 2*qf->c() ) ); // lifetime rms
  
}

// return lifetime mean
double LifetimeFit::get_lifeTime() const{
  return particle_lifetime_mean;
}

// return lifetime rms
double LifetimeFit::get_lifeTimeError() const{
  return particle_lifetime_rms;
}

// CAN THIS BE DELTED?????????????????????????????????
// return number of selected events
//unsigned int LifetimeFit::get_nAcc() const{
//  return nAcc;
//}

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

