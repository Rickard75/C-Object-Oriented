#include <cmath>
#include "Event.h"
#include "Utilities.h"
#include "Constants.h"
using namespace std;

double mass(const Event &ev) {

  // retrieve particles in the event
  //typedef const Particle* part_ptr; // already defined in class Event
  // const part_ptr* pop = ; // no need of defining a PoP, it's inside the object

  // variables to loop over particles
  int np = ev.get_nParticles();

  // positive / negative track counters, where declares 2 pointers
  int pos = 0;
  int neg = 0;

  // variables for momentum sums
  double sum_px = 0.0, sum_py = 0.0, sum_pz = 0.0;
  // variables for energy sums, for K0 and Lambda0
  double sum_eK0 = 0.0, sum_eL0 = 0.0;

  // loop over particles - momenta
  for ( int i=0; i<np; i++ ) {
    // get particle pointer
    const Event::part_ptr party = ev.get_particle(i); //single particle pointer = PoP[i]
    // update momentum sums
    sum_px += party->px;
    sum_py += party->py;
    sum_pz += party->pz;
    // update energy sums, for K0 and Lambda0 hypotheses:
    // pion mass for K0,
    // proton or pion mass for Lambda0,
    // for positive or negative particles respectively
    // here compute energy
    // update positive/negative track counters
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
  // check for exactly one positive and one negative track
  // otherwise return negative (unphysical, like for example -1) invariant mass to indicates a background event
  if((pos!=1) || (neg!=1)) return -1;
  //if(!(pos == 1 && neg == 1)) return -1;

  // invariant masses for different decay product mass hypotheses
  double mK0 = Utilities::invmass(sum_px, sum_py, sum_pz, sum_eK0); 
  double mL0 = Utilities::invmass(sum_px, sum_py, sum_pz, sum_eL0); 

  // compare invariant masses with known values and return the nearest one
  double diffK = fabs(Constants::massK0-mK0);
  double diffL = fabs(Constants::massLambda0-mL0);

  if(diffK<diffL){
    return mK0;
  } else {
    return mL0;
  }

}

