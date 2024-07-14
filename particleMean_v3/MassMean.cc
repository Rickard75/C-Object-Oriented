#include "MassMean.h"
#include "Event.h"

#include <cmath>

double mass( const Event& ev );


// constructor
MassMean::MassMean( double min, double max ):
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
MassMean::~MassMean() {
}


// add data from a new event
void MassMean::add( const Event& ev ) {

  // check for mass being in range
  // update number of events and sums
  double my_mass = mass(ev);
  if (min_mass <= my_mass && my_mass <= max_mass){
    my_mass -= get_min();
    
    sum_mass += my_mass;
    sum_sqr += my_mass*my_mass;
    nAcc++;
  }

}


// compute mean and rms
void MassMean::compute() {
  double my_mean = (this->sum_mass*1.0)/(this->nAcc);
  this->mean = my_mean;
  this->rms = sqrt((this->sum_sqr*1.0)/(this->nAcc)-pow(my_mean, 2.0));

  // rescaling
  this->mean += this->min_mass;
}


// return number of selected events
unsigned int MassMean::get_nAcc() const{
  return nAcc;
}


// return mean and rms
double MassMean::get_mean() const{
  return mean;
}
double MassMean::get_rms() const{
  return rms;
}


double MassMean::get_min() const {
  return min_mass;
}

