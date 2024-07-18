#include "ProperTime.h"
#include "Event.h"
#include "Utilities.h"
#include "Constants.h"
#include <iostream>
#include <cmath>

using namespace std;


// constructor
ProperTime::ProperTime() {
}

// destructor
ProperTime::~ProperTime() {
}

// recompute tag informations for new event
void ProperTime::update( const Event& ev ) {

  // set default quantities
  decay_type   = unknown;
  total_energy = -1.0;
  particle_mass   = -1.0;
  particle_time = -1.0;
  // code to compute total energy and invariant mass for the two mass hypotheses for the decay products
  // initializing variables
  int np = ev.get_nParticles();
  int pos = 0, neg = 0;
  double sum_px = 0.0, sum_py = 0.0, sum_pz = 0.0;
  double sum_eK0 = 0.0, sum_eL0 = 0.0;
  // loop over particles
  for (int i=0; i<np; i++){
    const Event::part_ptr party = ev.get_particle(i);
    sum_px += party->px;
    sum_py += party->py;
    sum_pz += party->pz;
    sum_eK0 += Utilities::energy (party->px, party->py, party->pz, Constants::massPion);
    if(party->chg == +1){
      sum_eL0 += Utilities::energy (party->px, party->py, party->pz, Constants::massProton);
      pos++;
    }
    if(party->chg == -1){
      sum_eL0 += Utilities::energy (party->px, party->py, party->pz, Constants::massPion);
      neg++;
    }
  }
  if((pos!=1) || (neg!=1)) return;
  double mK0 = Utilities::invmass(sum_px, sum_py, sum_pz, sum_eK0); 
  double mL0 = Utilities::invmass(sum_px, sum_py, sum_pz, sum_eL0);

  // compare invariant masses with known values and set final values
  // ( type, energy and mass )
  double diffK = fabs(Constants::massK0-mK0);
  double diffL = fabs(Constants::massLambda0-mL0);
  if(diffK<diffL){
    //return mK0;
    decay_type = K0;
    total_energy = sum_eK0;
    particle_mass = mK0;
  } else {
    //return mL0;
    decay_type = Lambda0;
    total_energy = sum_eL0;
    particle_mass = mL0;
  }

  // compute proper time
  
  double d = sqrt(pow(ev.get_x(),2)+pow(ev.get_y(),2)+pow(ev.get_z(),2));
  double m = particle_mass;
  double p = sqrt(pow(total_energy,2)-pow(m,2));
  double c = Constants::lightVelocity;
  particle_time = d*m/(p*c);

  return;

}

// return particle type
ProperTime::ParticleType ProperTime::get_type() {
  // check for new event and return result
  check();
  
  return decay_type;
}

// return total energy
double ProperTime::get_energy() {
    // check for new event and return result
    check();
    return total_energy;
  }

// return particle mass
double ProperTime::get_mass() {
  // check for new event and return result
  check();
  return particle_mass;
}

double ProperTime::get_time() {
  // check for new event and return result
  check();
  return particle_time;
}

/*
  BOOKMARK
  - use of check() function
  - correct spell of get_type(), root class are needed to be written
*/

