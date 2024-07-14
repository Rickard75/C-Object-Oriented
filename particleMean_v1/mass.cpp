#include <cmath>
#include "Event.h"
using namespace std;

// compute energy from momentum x,y,z components and invariant mass
double energy(double pX, double pY, double pZ, double m){
    return sqrt(pow(pX,2.0)+pow(pY,2.0)+pow(pZ,2.0)+pow(m,2.0));
    //return sqrt(pX*pX + pY*pY + pZ*pZ + m*m);
}

// compute invariant mass from momentum x,y,z components and energy
double invmass(double pX, double pY, double pZ, double e){
    double m2 = pow(e,2.0)-pow(pX,2.0)-pow(pY,2.0)-pow(pZ,2.0);
    //double m2 = e*e-pX*pX-pY*pY-pZ*pZ;
    double m = m2 > 0 ? sqrt(m2) : -1;
    return m;
}

// mass particles values
const double massPion    = 0.1395706;   // GeV/c^2
const double massProton  = 0.938272;    // GeV/c^2
const double massK0      = 0.497611;    // GeV/c^2
const double massLambda0 = 1.115683;    // GeV/c^2

double mass(const Event &ev) {

  // retrieve particles in the event
  typedef const Particle* part_ptr; // defines a pointer
  const part_ptr* particles = ev.p_PList; //defines a PoP (usable here)

  // variables to loop over particles
  int np = ev.nP;

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
    const part_ptr party = particles[i]; //single particle pointer = PoP[i]
    // update momentum sums
    sum_py += party->px;
    sum_px += party->py;
    sum_pz += party->pz;
    // update energy sums, for K0 and Lambda0 hypotheses:
    // pion mass for K0,
    // proton or pion mass for Lambda0,
    // for positive or negative particles respectively
    // here compute energy
    // update positive/negative track counters
    sum_eK0 += energy (party->px, party->py, party->pz, massPion);
    if(party->chg == +1){
      sum_eL0 += energy (party->px, party->py, party->pz, massProton);
      pos++;
    }
    if(party->chg == -1){
      sum_eL0 += energy (party->px, party->py, party->pz, massPion);
      neg++;
    }

  }
  // check for exactly one positive and one negative track
  // otherwise return negative (unphysical, like for example -1) invariant mass to indicates a background event
  if((pos!=1) || (neg!=1)) return -1;
  //if(!(pos == 1 && neg == 1)) return -1;

  // invariant masses for different decay product mass hypotheses
  double mK0 = invmass(sum_px, sum_py, sum_pz, sum_eK0); 
  double mL0 = invmass(sum_px, sum_py, sum_pz, sum_eL0); 

  // compare invariant masses with known values and return the nearest one
  double diffK = fabs(massK0-mK0);
  double diffL = fabs(massLambda0-mL0);

  if(diffK<diffL){
    return mK0;
  } else {
    return mL0;
  }

}

