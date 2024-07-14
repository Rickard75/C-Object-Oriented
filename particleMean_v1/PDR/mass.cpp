... include header files ...

// compute energy from momentum x,y,z components and invariant mass
double ...( ... ) {
  ...
}

// compute invariant mass from momentum x,y,z components and energy
double ...( ... ) {
  ...
}

// mass particles values
const double massPion    = 0.1395706;   // GeV/c^2
const double massProton  = 0.938272;    // GeV/c^2
const double massK0      = 0.497611;    // GeV/c^2
const double massLambda0 = 1.115683;    // GeV/c^2

double mass( ... ) {

  // retrieve particles in the event
  typedef const Particle* part_ptr; // defines a pointer
  const part_ptr* particles = ...

  // variables to loop over particles
  ...

  // positive / negative track counters, where declares 2 pointers
  ...

  // variables for momentum sums
  ...
  // variables for energy sums, for K0 and Lambda0
  ...

  // loop over particles - momenta
  ... ( ... ) {
    // get particle pointer
    ...
    // update momentum sums
    ...
    // update energy sums, for K0 and Lambda0 hypotheses:
    // pion mass for K0,
    // proton or pion mass for Lambda0,
    // for positive or negative particles respectively
    ... // here compute energy
    // update positive/negative track counters
    ...
  }
  // check for exactly one positive and one negative track
  // otherwise return negative (unphysical, like for example -1) invariant mass to indicates a background event
  ...

  // invariant masses for different decay product mass hypotheses
  ... // compute masses

  // compare invariant masses with known values and return the nearest one
  ...

}

