#ifndef LifetimeFit_h
#define LifetimeFit_h

#include <vector>
class Event;

class LifetimeFit {

 public:

  // CONSTRUCTOR
  LifetimeFit( double min, double max, double min_time, double max_time, double min_scan, double max_scan, double scan_step ); // mass range
  ~LifetimeFit();

  bool add( const Event& ev );      // add data from a new event
  void compute();                   // compute mean and rms

  
  unsigned int get_nAcc() const;    // CAN THIS BE DELETED????????????????
  double get_lifeTime() const;      // return mean lifetime
  double get_lifeTimeError() const; // return error on mean lifetime
 
 private:

  double min_mass; 
  double max_mass; 
  double min_time; // min time
  double max_time; // max time
  double min_scan; // min scan
  double max_scan; // max scan
  double scan_step; // scan step
  std::vector<double> times; // container for times
  double particle_lifetime_mean; // lifetime mean
  double particle_lifetime_rms; // lifetime rms


};

#endif

