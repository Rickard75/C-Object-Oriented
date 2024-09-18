#ifndef LifetimeFit_h
#define LifetimeFit_h

#include <vector>
class Event;
class ParticleReco;

class LifetimeFit {

 public:

  
  LifetimeFit( double min, double max, 
               double min_time, double max_time, 
               double min_scan, double max_scan, double scan_step ); // constructor
  ~LifetimeFit(); // destructor

  bool add( const Event& ev );      // add data from a new event
  void compute();                   // compute mean and rms

  
  unsigned int get_nAcc() const;    // NEW: now based on lifetimes accepted
  double get_lifeTime() const;      // return mean lifetime
  double get_lifeTimeError() const; // return error on mean lifetime
 
 private:

  double min_mass; // mass range
  double max_mass; 
  double min_time; // time range
  double max_time; 
  double min_scan; // scan range
  double max_scan;
  double scan_step; // scan step
  std::vector<double> times; // container for times
  double particle_lifetime_mean; // lifetime mean
  double particle_lifetime_rms; // lifetime rms


};

#endif

